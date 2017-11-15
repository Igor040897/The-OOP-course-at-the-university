// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "Room.hpp"
#include "ArtificialHouseplant.hpp"
#include "FoliarHouseplant.hpp"
#include "FruitingHouseplant.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST(test_create_floweringHouseplant_good_watering)
{
	Room room;

	room.addPlant(std::make_unique<FloweringHouseplant>("FloweringHouseplant", 5, 2, 2, 2));
	for (int i = 0; i < 7; i++) {//2 congratulations
		room.watering();
		room.passedNextDay();
		room.passedNextDay();
	}
	assert(dynamic_cast<FloweringHouseplant *>(room.getPlant("FloweringHouseplant"))->getCurrentNeedTrueWatering() == 6);
}

DECLARE_OOP_TEST(test_create_floweringHouseplant_bad_watering)
{
	Room room;

	room.addPlant(std::make_unique<FloweringHouseplant>("FloweringHouseplant", 5, 2, 2, 2));
	room.watering();
	room.passedNextDay();
	room.watering();
	room.passedNextDay();
	room.passedNextDay();
	room.passedNextDay();
	room.watering();
	room.passedNextDay();
	room.watering();
	assert(dynamic_cast<FloweringHouseplant *>(room.getPlant("FloweringHouseplant"))->getCurrentCountTrueWatering() == 0);
	room.passedNextDay();
	room.passedNextDay();
	room.watering();
	assert(dynamic_cast<FloweringHouseplant *>(room.getPlant("FloweringHouseplant"))->getCurrentCountTrueWatering() == 1);
	room.passedNextDay();
	room.passedNextDay();
	room.passedNextDay();
	room.passedNextDay();
	room.watering();
	assert(dynamic_cast<FloweringHouseplant *>(room.getPlant("FloweringHouseplant"))->getCurrentCountTrueWatering() == 0);
}

DECLARE_OOP_TEST ( test_create_FruitingHouseroom_Bloom_And_Fruiting)
{
	Room room;
	room.addPlant(std::make_unique<FruitingHouseplant>("Tree", 2, 2, 2, 2, "Lemon", 2));

	for (int i = 0; i < 3; i++) {
		room.watering();
		room.passedNextDay();
		room.passedNextDay();
	}

	assert((dynamic_cast<FruitingHouseplant *>(room.getPlant("Tree"))->isFruiting()));
	assert((dynamic_cast<FruitingHouseplant *>(room.getPlant("Tree"))->getCurrentNeedTrueWatering() == 4));
	assert((dynamic_cast<FruitingHouseplant *>(room.getPlant("Tree"))->getCurrentCountTrueWatering() == 0));
	room.passedNextDay();
	room.watering();
	assert((dynamic_cast<FruitingHouseplant *>(room.getPlant("Tree"))->getCurrentCountTrueWatering() == 0));
	assert(!(dynamic_cast<FruitingHouseplant *>(room.getPlant("Tree"))->isBloom()));
	assert(!(dynamic_cast<FruitingHouseplant *>(room.getPlant("Tree"))->isFruiting()));

	room.passedNextDay();
	room.passedNextDay();
	room.watering();
	assert((dynamic_cast<FruitingHouseplant *>(room.getPlant("Tree"))->getCurrentCountTrueWatering() == 1));
	room.passedNextDay();
	room.passedNextDay();
	room.passedNextDay();
	room.passedNextDay();
	room.watering();
	assert((dynamic_cast<FruitingHouseplant *>(room.getPlant("Tree"))->getCurrentCountTrueWatering() == 0));
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_FoliarHouseroom)
{
	Room room;
	room.addPlant(std::make_unique<FoliarHouseplant>("FoliarHouseroom", 5, 2, 249, room));

	room.passedNextDay();
	room.watering();//первый полив не считается
	room.passedNextDay();
	room.passedNextDay();
	assert(room.getCountPlant() == 1);
	assert((dynamic_cast<FoliarHouseplant *>(room.getPlant("FoliarHouseroom"))->getHeight() == 249));

	room.watering();
	assert((dynamic_cast<FoliarHouseplant *>(room.getPlant("FoliarHouseroom"))->getHeight() == 125));
	assert(room.getCountPlant() == 2);
	room.passedNextDay();
	room.passedNextDay();
	room.passedNextDay();
	room.watering();
	assert((dynamic_cast<FoliarHouseplant *>(room.getPlant("FoliarHouseroom"))->getHeight() == 126));
	room.passedNextDay();
	room.watering();
	assert((dynamic_cast<FoliarHouseplant *>(room.getPlant("FoliarHouseroom"))->getHeight() == 127));
	room.watering();
	assert((dynamic_cast<FoliarHouseplant *>(room.getPlant("FoliarHouseroom"))->getHeight() == 127));

}


/*****************************************************************************/


DECLARE_OOP_TEST( test_create_ArtificialHouseroom)
{
	Room room;
	room.addPlant(std::make_unique<ArtificialHouseplant>("ArtificialHouseroom", 5));

	room.passedNextDay();
	room.watering();
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_create_a_lot_of_plants)
{
	Room room;
	room.addPlant(std::make_unique<FloweringHouseplant>("FloweringHouseplant", 5, 2, 2, 2));
	room.addPlant(std::make_unique<FruitingHouseplant>("Tree", 2, 2, 2, 2, "Lemon", 2));
	room.addPlant(std::make_unique<FoliarHouseplant>("FoliarHouseroom", 5, 2, 249, room));
	room.addPlant(std::make_unique<ArtificialHouseplant>("ArtificialHouseroom", 5));

	assert(room.getCountPlant() == 4);

	for (int i = 0; i < 4; i++) {//2 congratulations
		room.watering();
		room.passedNextDay();
		room.passedNextDay();
	}

	assert(room.getCountPlant() == 5);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_FloweringHouseplant_error)
{
	Room room;

	ASSERT_THROWS(room.addPlant(std::make_unique<FloweringHouseplant>("", 5, 2, 2, 2)),
		Messages::NamePlantEmpty
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FloweringHouseplant>("FloweringHouseplant", -1, 2, 2, 2)),
		Messages::NegativeAge
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FloweringHouseplant>("FloweringHouseplant", 5, -1, 2, 2)),
		Messages::NegativePeriodWatering
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FloweringHouseplant>("FloweringHouseplant", 5, 1, 0, 2)),
		Messages::NegativeFloweringDuration
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FloweringHouseplant>("FloweringHouseplant", 5, 1, -1, 2)),
		Messages::NegativeFloweringDuration
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FloweringHouseplant>("FloweringHouseplant", 5, 1, 5, -1)),
		Messages::NegativeCountWatering
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FloweringHouseplant>("FloweringHouseplant", 5, 7, 1, 0)),
		Messages::NegativeCountWatering
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_FruitingHouseplant_error)
{
	Room room;

	ASSERT_THROWS(room.addPlant(std::make_unique<FruitingHouseplant>("", 2, 2, 2, 2, "Lemon", 2)),
		Messages::NamePlantEmpty
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FruitingHouseplant>("FruitingHouseplant", -5, 2, 2, 2, "Lemon", 2)),
		Messages::NegativeAge
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FruitingHouseplant>("FruitingHouseplant", 2, -7, 2, 2, "Lemon", 2)),
		Messages::NegativePeriodWatering
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FruitingHouseplant>("FruitingHouseplant", 2, 2, -3, 2, "Lemon", 2)),
		Messages::NegativeFloweringDuration
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FruitingHouseplant>("FruitingHouseplant", 2, 2, 2, -2, "Lemon", 2)),
		Messages::NegativeCountWatering
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FruitingHouseplant>("FruitingHouseplant", 2, 2, 2, 2, "", 2)),
		Messages::NameFrutitEmpty
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FruitingHouseplant>("FruitingHouseplant", 2, 2, 2, 2, "Lemon", -9)),
		Messages::NegativeDurationFruiting
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_FoliarHouseplant_error)
{
	Room room;

	ASSERT_THROWS(room.addPlant(std::make_unique<FoliarHouseplant>("", 5, 2, 249, room)),
		Messages::NamePlantEmpty
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FoliarHouseplant>("FoliarHouseplant", -4, 2, 249, room)),
		Messages::NegativeAge
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FoliarHouseplant>("FoliarHouseplant", 5, -3, 249, room)),
		Messages::NegativePeriodWatering
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FoliarHouseplant>("FoliarHouseplant", 5, 2, -5, room)),
		Messages::NegativeHeight
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<FoliarHouseplant>("FoliarHouseplant", 5, 2, 0, room)),
		Messages::NegativeHeight
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_ArtificialHouseplant_error)
{
	Room room;

	ASSERT_THROWS(room.addPlant(std::make_unique<ArtificialHouseplant>("", 5)) ,
		Messages::NamePlantEmpty
	);
	ASSERT_THROWS(room.addPlant(std::make_unique<ArtificialHouseplant>("ArtificialHouseplant", -5)) ,
		Messages::NegativeAge
	);
}

