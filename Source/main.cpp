/* Created Day 1 */
#include <iostream>
#include <vector>

using namespace std;


#include "raylib.h"

#include "player.h"
#include "falling.h"
#include "highscore.h"

enum Screen
{
	MAIN_MENU = 0,
	ABOUT     = 1,
	PLAYING   = 2,
};

const int windowX = 800;
const int windowY = 600;

const char *title = "SpaceScore 15"; // Placeholder - change later

EntityPlayer player;

bool soundPlayed = false;

Screen currentScreen = MAIN_MENU;

void DrawPlayingScreen();
void DrawMenu();
void DrawAbout();

int main()
{
	InitWindow(
		windowX,
		windowY,
		title
	);

	SetTargetFPS( 60 );
	InitAudioDevice();

	// Load textures
	Texture groundTexture = LoadTexture( "images/ground.png" );
	player.LoadTex();

	// Load sounds
	Sound high = LoadSound( "sound/high.wav" );
	Sound gameover = LoadSound( "sound/gameover.wav" );

	while ( !WindowShouldClose() )
	{
		BeginDrawing();
		ClearBackground( LIGHTGRAY ); // Perfect color

		DrawTexture( groundTexture, 0, 550, WHITE );

		if ( currentScreen == PLAYING )
		{
			if (player.isAlive)
			{
				DrawPlayingScreen();
			}
			else
			{
				ClearBackground( BLACK );

				DrawText( TextFormat( "Your score: %0i", player.score ), 20, 45, 20, WHITE );
				DrawText( TextFormat( "HighScore: %0i", ReadHighScore() ), 20, 65, 20, WHITE );

				DrawText( "Press space to restart",  20, 85, 20, YELLOW );

				if ( player.score >= ReadHighScore() )
				{
					WriteHighScore( player.score );
					DrawText( "\"Top Shelf!\" - Spy from Team Fortress 2", 20, 20, 25, GREEN );

					if ( !soundPlayed )
					{
						PlaySound( high );
						soundPlayed = true;
					}
				}
				else
				{
					if ( !soundPlayed )
					{
						PlaySound( gameover );
						soundPlayed = true;
					}

					DrawText( "\"Not our finest moment\" - Spy from Team Fortress 2", 20, 20, 25, RED );
				}

				if ( IsKeyPressed( 32 ) )
				{
					player.ResetPlayer();
					soundPlayed = false;
				}
			}
		}
		else if ( currentScreen == MAIN_MENU )
		{
			DrawMenu();
		}
		else
		{
			DrawAbout();
		}

		EndDrawing();
	} 
}

void DrawPlayingScreen()
{
	player.Update();
	player.Draw();

	// Draw ui
	DrawText( TextFormat( "SCORE: %0i", player.score ), 10, 10, 24, BLACK );
	DrawText( TextFormat( "BULLETS: %02i", player.bulletCount ), 10, 10 + 24, 24, BLACK );
	DrawText( TextFormat( "HP: %0i", player.hp ), 10, 10 + (24*2), 24, BLACK );
}

void DrawMenu()
{
	DrawText( "------ AGILE ------", 40, 40, 50, BLACK );
	DrawText( "[A KEY] PLAY", 30, 110, 30, BLACK );
	DrawText( "[B KEY] ABOUT", 30, 150, 30, BLACK );

	if ( IsKeyPressed( 66 ) )
	{
		cout << "Did it work" << endl;
		currentScreen = ABOUT;
	}
	else if ( IsKeyPressed( 65 ) )
	{
		currentScreen = PLAYING;
	}
}

void DrawAbout()
{
	// Yikes. That's a really long line
	DrawText( "Agile was created for the 15th ScoreSpace Jam in 3 days by pointThink\nusing C++ and RayLib\n\nShoot the boxes to get points\n\nThere are 4 types of boxes:\nRed: It damages you when you touch it\nGreen: It gives you 1 hp when you touch it\nYellow: Gives you a bullet when you touch it\nBlue: Gives you 300 points when you touch it\n\nControls:\nW - Jump\nA - Move Left\nD - Move right\nSpace - Shoot\n\nPress space to go back to main menu", 10, 10, 20, BLACK );

	if ( IsKeyPressed (32) )
		currentScreen = MAIN_MENU;
}