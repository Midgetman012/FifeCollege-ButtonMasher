// Included Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>


// entry point for the program
int main()
{
	// Game setup


	// Make a variable called gameWindow of type RenderWindow
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Button Masher", 
		sf::Style::Titlebar | sf::Style::Close);

	// Create button sprite
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("graphics/button.png");

	sf::Sprite buttonSprite;
	buttonSprite.setTexture(buttonTexture);


	// Create music
	sf::Music gameMusic;
	gameMusic.openFromFile ("audio/music.ogg");
	gameMusic.play();

	// Create font
	sf::Font gameFont;
	gameFont.loadFromFile("fonts/mainfont.ttf");

	// Create Title
	sf::Text titleText;
	titleText.setFont(gameFont);
	titleText.setString("Button Masher!");
	titleText.setCharacterSize(100);
	titleText.setFillColor(sf::Color::Red);
	titleText.setStyle(sf::Text::Bold | sf::Text::Italic);
	titleText.setPosition(gameWindow.getSize().x / 2 - titleText.getLocalBounds().width / 2, 30);

	sf::Text authorText;
	authorText.setFont(gameFont);
	authorText.setString("By Rob Boss!");
	authorText.setCharacterSize(100);
	authorText.setFillColor(sf::Color::Red);
	authorText.setStyle(sf::Text::Bold | sf::Text::Italic);
	authorText.setPosition(gameWindow.getSize().x / 2 - authorText.getLocalBounds().width / 2, 100);

	// Score
	int score = 0;

	// score text
	sf::Text scoreText;
	scoreText.setFont(gameFont);
	scoreText.setString("Score : " + std::to_string(score));
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setPosition(30, 30);

	// timer text
	sf::Text timerText;
	timerText.setFont(gameFont);
	timerText.setString("Time remaining: 0 ");
	timerText.setCharacterSize(16.0f);
	timerText.setFillColor(sf::Color::Red);
	timerText.setPosition(gameWindow.getSize().x - timerText.getLocalBounds().width - 30, 30);

	// Timer functionality
	sf::Time TimeLimit = sf::seconds(10.0f);
	sf::Time timeRemaining = TimeLimit;
	sf::Clock gameClock;


	//click sound effect
	sf::SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("audio/buttonclick.ogg");
	sf::Sound clickSound;
	clickSound.setBuffer(clickBuffer);

	//Game state
	bool playing = false;
	//Centre the sprite on screen

	buttonSprite.setPosition(
		gameWindow.getSize().x / 2 - buttonTexture.getSize().x / 2,
		gameWindow.getSize().y / 2 - buttonTexture.getSize().y / 2);


	// Game Loop
	// Game setup
	// Runs every frame until the game window is closed
	while (gameWindow.isOpen())
	{
		// Check for input
		sf::Event gameEvent;
		while (gameWindow.pollEvent(gameEvent))
		{
			// Process events

			// Check if the event is a mouse button pressed event
			if (gameEvent.type == sf::Event::MouseButtonPressed)
			{
				if (buttonSprite.getGlobalBounds().contains(gameEvent.mouseButton.x, gameEvent.mouseButton.y))
				{
					// We clicked the button woop woop
					//Is the game playing
					if (playing == true)
					{
						//yes
						score = score + 1;
					}
					else
					{
						//naw
						playing = true;
					}
					//Click button sound effect
					clickSound.play();
				}
			}

			// Check if the event is the closed event
			if (gameEvent.type == sf::Event::Closed)
			{
				// Close the game window
				gameWindow.close();
			}
		}

		// Update game state
		sf::Time frameTime = gameClock.restart();
		if (playing == true)
		{
			timeRemaining = timeRemaining - frameTime;

			if (timeRemaining.asSeconds() <= 0.0f)
			{
				timeRemaining = sf::seconds(0.0f);
				playing = false;
			}
		}
		
		timerText.setString("Time remaining: " + std::to_string((int)std::ceilf(timeRemaining.asSeconds())));

		scoreText.setString("Score : " + std::to_string(score));

		//Clear the window to a specific colour
		gameWindow.clear(sf::Color::Black);

		//Draw everything
		gameWindow.draw(buttonSprite);
		gameWindow.draw(titleText);
		gameWindow.draw(authorText);
		gameWindow.draw(scoreText);
		gameWindow.draw(timerText);

		//Display the window contents on the screen
		gameWindow.display();
	}

	// exit point for the program
	return 0;
}