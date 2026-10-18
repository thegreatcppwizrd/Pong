#include <iostream>
#include "raylib.h"

Color Green = Color{ 38, 185, 154, 255 }; 
Color Dark_Green = Color{ 20, 160, 133, 255 };
Color Light_Green = Color{ 129, 204, 184, 255 };
Color Yellow = Color{ 243, 213, 91, 255 };


int player_score = 0;
int cpu_score = 0;

class Ball
{
public:
	Vector2 ballVeloicty = { -6, -6 };
	float x, y;
	int radius;

	void Draw()
	{
		DrawCircle(x, y, radius, Yellow);
	}

	void Update()
	{
		x += ballVeloicty.x;
		y += ballVeloicty.y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			ballVeloicty.y *= -1;
			//ballVeloicty.x *= -1;
		}
		if (x + radius >= GetScreenWidth())
		{
			cpu_score++;
			ResetBall();
		}
		if (x - radius <= 0)
		{
			player_score++;
			ResetBall();
		}
	}

	void ResetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;
		
		int speed_choices[2] = { -6, 6 };
		ballVeloicty.x = speed_choices[GetRandomValue(0, 1)];
		ballVeloicty.y = speed_choices[GetRandomValue(0, 1)];
	 
	}
};

class Paddle
{
protected:
	void LimitMovement()
	{
		if (y + height >= GetScreenHeight())
		{
			y = GetScreenHeight() - height - 10;
		}

		if (y <= 0)
		{
			y = 0;
		}
	}

public:
	float x, y;
	float width, height;
	int speed;

	void Draw()
	{
		DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
	}
	void Update()
	{
		if (IsKeyDown(KEY_UP))
		{
			y -= speed;
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			y += speed;
		}

		LimitMovement();
	}

};

Ball ball;
Paddle player;


class CpuPaddle : public Paddle
{
public:
	void Update(float ball_y)
	{
			

		float paddleCenter = y + height / 2.0f;
		float deadZone = GetRandomValue(60, 100);

		if (paddleCenter < ball_y - deadZone)
			y += speed;
		else if (paddleCenter > ball_y + deadZone)
			y -= speed;

		LimitMovement();
		
	}
}; //height / 2 != ball_y

CpuPaddle cpu;

int main()
{
	InitAudioDevice();
	std::cout << "Starting the game" << std::endl;

	const int screen_width = 1280;
	const int screen_height = 800;

	InitWindow(screen_width, screen_height, "Pong");
	SetTargetFPS(60);

	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;


	player.width = 25;
	player.height = 120;
	player.x = screen_width - player.width - 10;
	player.y = screen_height / 2 - player.height / 2; 
	player.speed = 7;

	cpu.width = 25;
	cpu.height = 120;
	cpu.x = 10;
	cpu.y = screen_height / 2 - player.height / 2;
	cpu.speed = 7;

	float time = 0.0f;
	Sound paddle_bounce = LoadSound("./resources/paddleBounce.mp3");
	SetSoundVolume(paddle_bounce, 10.0f);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		//Updating
		ball.Update();
		player.Update();
		cpu.Update(ball.y);
		 
		//Checking for colision
		
		if (CheckCollisionCircleRec(Vector2 {ball.x, ball.y}, ball.radius, Rectangle {player.x, player.y, player.width, player.height}))
		{
			ball.x = player.x - ball.radius;

			float paddleCenter = player.y + player.height / 2.0f;

			float hitOffset =
				(ball.y - paddleCenter) / (player.height / 2.0f);

			ball.ballVeloicty.x = -7.0f;
			ball.ballVeloicty.y = hitOffset * 7.0f;
			PlaySound(paddle_bounce);
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
		{
			ball.x = cpu.x + cpu.width + ball.radius;

			float paddleCenter = ball.y + cpu.height / 2.0f;

			float hitOffset =
				(ball.y - paddleCenter) / (cpu.height / 2.0f);

			ball.ballVeloicty.x = 7.0f;
			ball.ballVeloicty.y = hitOffset * 7.0f;

			PlaySound(paddle_bounce);
		}

		//Drawing 
		ClearBackground(Dark_Green);

		DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
		DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);

		ball.Draw();
		player.Draw();
		cpu.Draw();

		DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
		DrawLine(screen_width/2, 0, screen_width / 2, screen_height, WHITE);

		EndDrawing();
	}

	CloseWindow();
}