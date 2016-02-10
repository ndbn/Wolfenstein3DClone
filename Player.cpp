#include "Player.hpp"
#include "Utility.hpp"
#include "Level.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


Player::Player(const Level& mLevel, const Vector3f& position)
	: mCamera(position)
	, mMouseLocked(false)
	, mMovement()
	, mLevel(mLevel)
{
}

void Player::update(sf::Time dt, sf::RenderWindow& window)
{
	const static float Sensitivity = 0.5f;
	const static float Speed = 5;
	const static float MovementAmount = Speed * dt.asSeconds();
	const static float PlayerSize = 0.2f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		window.setMouseCursorVisible(true);
		mMouseLocked = false;
	}

	if (!window.hasFocus())
	{
		window.setMouseCursorVisible(true);
		mMouseLocked = false;
	}

	if (mMouseLocked)
	{
		sf::Vector2i centerPosition = sf::Vector2i(window.getSize().x / 2u, window.getSize().y / 2u);
		sf::Vector2i deltaPos = sf::Mouse::getPosition(window) - centerPosition;

		bool rotY = deltaPos.x != 0;
		bool rotX = deltaPos.y != 0;

		if (rotY)
			mCamera.rotateY(ToRadian(deltaPos.x * Sensitivity));
		if (rotX)
			mCamera.rotateX(ToRadian(deltaPos.y * Sensitivity));

		if (rotY || rotX)
			sf::Mouse::setPosition(centerPosition, window);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus())
	{
		sf::Vector2i centerPosition = sf::Vector2i(window.getSize().x / 2u, window.getSize().y / 2u);
		window.setMouseCursorVisible(false);
		sf::Mouse::setPosition(centerPosition, window);
		mMouseLocked = true;
	}
	mMovement = Zero;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		mMovement += mCamera.getForward();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		mMovement -= mCamera.getForward();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		mMovement += mCamera.getLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		mMovement += mCamera.getRight();

	mMovement.y = 0;
	if(mMovement.length() > 0)
		mMovement = mMovement.normalized();

	Vector3f oldPosition = mCamera.getPosition();
	Vector3f mewPosition = oldPosition +  mMovement * MovementAmount;

	Vector3f collision = mLevel.checkCollision(oldPosition, mewPosition, PlayerSize, PlayerSize);

	mMovement *= collision;

	mCamera.move(mMovement, MovementAmount);
}
void Player::draw()
{
}