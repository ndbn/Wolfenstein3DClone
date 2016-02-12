#include "Door.hpp"
#include "Utility.hpp"


Door::Door(const Vector3f& poisition, const Vector3f& rotation, const Material& material)
	: mTransform(poisition, rotation)
	, mShader()
	, mMaterial(material)
	, mIsOpening(false)
	, mOpenPosition(rotation.y == 90 ? poisition - Vector3f(0, 0, 0.9f) : poisition - Vector3f(0.9f, 0, 0))
	, mClosePosition(poisition)
	, mOpeningStartTime()
	, mOpenTime()
	, mClosingStartTime()
	, mCloseTime()
	, mTimer(sf::Time::Zero)
{
	Vertex vertices[] =
	{
		{ { START,	START,	START	},	{ 0.5f,		1		} },
		{ { START,	HEIGHT,	START	},	{ 0.5f,		0.75f	} },
		{ { WIDTH,	HEIGHT,	START	},	{ 0.75f,	0.75f	} },
		{ { WIDTH,	START,	START	},	{ 0.75f,	1		} },

		{ { START,	START,	START	},	{ 0.73f,	1		} },
		{ { START,	HEIGHT,	START	},	{ 0.73f,	0.75f	} },
		{ { START,	HEIGHT,	LENGTH	},	{ 0.75f,	0.75f	} },
		{ { START,	START,	LENGTH	},	{ 0.75f,	1		} },

		{ { START,	START,	LENGTH },	{ 0.5f,		1		} },
		{ { START,	HEIGHT,	LENGTH },	{ 0.5f,		0.75f	} },
		{ { WIDTH,	HEIGHT,	LENGTH },	{ 0.75f,	0.75f	} },
		{ { WIDTH,	START,	LENGTH },	{ 0.75f,	1		} },

		{ { WIDTH,	START,	START	},	{ 0.73f,	1		} },
		{ { WIDTH,	HEIGHT,	START	},	{ 0.73f,	0.75f	} },
		{ { WIDTH,	HEIGHT,	LENGTH	},	{ 0.75f,	0.75f	} },
		{ { WIDTH,	START,	LENGTH	},	{ 0.75f,	1		} }
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3,

		6, 5, 4,
		7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15
	};

	mMesh.addVertices(vertices, ARRAY_SIZE(vertices), indices, ARRAY_SIZE(indices));
}

void Door::open(sf::Time dt)
{
	if (mIsOpening)
		return;

	mOpeningStartTime = dt.asSeconds();
	mOpenTime = mOpeningStartTime + TIME_TO_OPEN;
	mClosingStartTime = mOpenTime + CLOSE_DELAY;
	mCloseTime = mClosingStartTime + TIME_TO_OPEN;
	mTimer = sf::Time::Zero;
	mIsOpening = true;
}

void Door::update(sf::Time dt)
{
	mTimer += dt;

	if (mIsOpening)
	{
		if (mTimer.asSeconds() < mOpenTime)
		{
			float factor = (mTimer.asSeconds() - mOpeningStartTime) / TIME_TO_OPEN;
			mTransform.setPosition(Vector3f::lerp(mClosePosition, mOpenPosition, factor));
			
		}
		else if (mTimer.asSeconds() < mClosingStartTime)
		{
			mTransform.setPosition(mOpenPosition);
		}
		else if (mTimer.asSeconds() < mCloseTime)
		{
			float factor = (mTimer.asSeconds() - mClosingStartTime) / TIME_TO_OPEN;
			mTransform.setPosition(Vector3f::lerp(mOpenPosition, mClosePosition, factor));
		}
		else
		{
			mTimer = sf::Time::Zero;
			mTransform.setPosition(mClosePosition);
			mIsOpening = false;
		}
	}
}

void Door::draw()
{
	mShader.updateUniforms(mTransform.getProjectedTransformation(), mMaterial);
	mMesh.draw();
}

Vector3f Door::getPosition() const
{
	return mTransform.getPosition();
}

Vector2f Door::getSize() const
{
	if (mTransform.getRotation().y == 90)
		return{ LENGTH, WIDTH };
	else
		return{ WIDTH, LENGTH };
}