// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/

void createCommonConfiguration(Controller & c)
{

	c.createStation("Bohodukhiv", 2);
	c.createStation("Ohtirka", 2);
	c.createStation("Poltava", 3);
	c.createStation("Kharkov", 2);
	c.createStation("Zenkov", 3);
	c.createStation("Kremenchug", 3);
	c.createStation("Gadyach", 2);
	c.createStation("Kiev", 6);
	c.createStation("Lviv", 4);
	c.createStation("Sumy", 3);

	c.createTrain(1349, 30);
	c.createTrain(2468, 45);
	c.createTrain(4382, 38);
	c.createTrain(1111, 30);
	c.createTrain(8585, 45);
	c.createTrain(7777, 38);

	c.createRoute(79);
	c.createRoute(19);
	c.createRoute(33);
	c.createRoute(15);
	c.createRoute(28);
	c.createRoute(31);

	c.addScheduleToRoute("18:00", "18:10", "Ohtirka", 79);
	c.addScheduleToRoute("19:45", "19:55", "Bohodukhiv", 79);
	c.addScheduleToRoute("21:00", "21:10", "Kharkov", 79);

	c.addScheduleToRoute("08:35", "08:45", "Bohodukhiv", 19);
	c.addScheduleToRoute("10:45", "10:55", "Poltava", 19);
	c.addScheduleToRoute("12:00", "12:10", "Zenkov", 19);
	c.addScheduleToRoute("12:10", "13:00", "Ohtirka", 19);

	c.addScheduleToRoute("11:25", "11:35", "Poltava", 33);
	c.addScheduleToRoute("13:25", "13:35", "Kremenchug", 33);
	c.addScheduleToRoute("17:35", "17:45", "Gadyach", 33);
	c.addScheduleToRoute("18:40", "18:50", "Zenkov", 33);
	c.addScheduleToRoute("19:30", "19:40", "Ohtirka", 33);
	c.addScheduleToRoute("19:50", "20:00", "Bohodukhiv", 33);
	c.addScheduleToRoute("21:00", "21:10", "Kharkov", 33);

	c.addScheduleToRoute("09:25", "09:35", "Poltava", 15);
	c.addScheduleToRoute("16:45", "16:55", "Kiev", 15);

	c.addScheduleToRoute("19:25", "19:35", "Bohodukhiv", 28);
	c.addScheduleToRoute("21:05", "21:15", "Kharkov", 28);

	c.addScheduleToRoute("19:45", "19:55", "Bohodukhiv", 31);
	c.addScheduleToRoute("21:00", "21:10", "Ohtirka", 31);

	c.runningTrainOnRoute(19, 1349);
	c.runningTrainOnRoute(79, 8585);
	c.runningTrainOnRoute(33, 2468);
	c.runningTrainOnRoute(15, 1111);
	c.runningTrainOnRoute(28, 4382);
	c.runningTrainOnRoute(31, 7777);
}

/*****************************************************************************/

DECLARE_OOP_TEST ( test_print_five_station_with_max_count_route)
{
	Controller c;
	createCommonConfiguration(c);
	
	std::stringstream fiveTest;
	fiveTest << "Bohodukhiv=5; Ohtirka=4; Poltava=3; Kharkov=3; Zenkov=2" << '\0';
	std::stringstream const & five = c.fiveStationWithMaxCountRoute();

	assert(fiveTest.str() == five.str());
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_five_route_with_the_longest_travel_time)
{
	Controller c;
	createCommonConfiguration(c);

	std::stringstream fiveTest;
	fiveTest << "Number of the route = 33: Start = Poltava; Finish = Kharkov; the duration of the road : 9/35; ";
	fiveTest << "Number of the route = 15: Start = Poltava; Finish = Kiev; the duration of the road : 7/20; ";
	fiveTest << "Number of the route = 19: Start = Bohodukhiv; Finish = Ohtirka; the duration of the road : 3/35; ";
	fiveTest << "Number of the route = 79: Start = Ohtirka; Finish = Kharkov; the duration of the road : 3/0; ";
	fiveTest << "Number of the route = 28: Start = Bohodukhiv; Finish = Kharkov; the duration of the road : 1/40" << '\0';
	std::stringstream const & five = c.fiveRouteWithTheLongestTravelTime();

	assert(fiveTest.str() == five.str());
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_couples_station_involving_more_than_two_routes)
{
	Controller c;
	createCommonConfiguration(c);

	std::stringstream fiveTest;
	fiveTest << "Flight: Bohodukhiv - Kharkov; Flight: Ohtirka - Bohodukhiv; Flight: Zenkov - Ohtirka" << '\0';
	std::stringstream const & five = c.couplesStationInvolvingMoreThanTwoRoutes();

	assert(fiveTest.str() == five.str());
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_stations_without_route)
{
	Controller c;
	createCommonConfiguration(c);

	std::stringstream fiveTest;
	fiveTest << "Stations: Lviv; Sumy" << '\0';
	std::stringstream const & five = c.stationsWithoutRoute();

	assert(fiveTest.str() == five.str());
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_not_enough_platforms)
{
	Controller c;
	createCommonConfiguration(c);

	std::stringstream fiveTest;
	fiveTest << "Bohodukhiv; Kharkov" << '\0';
	std::stringstream const & five = c.notEnoughPlatforms();

	assert(fiveTest.str() == five.str());
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_create_station_empty_name)
{
	Controller c;
	ASSERT_THROWS(c.createStation("", 5),
		Messages::NameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_create_station_negative_count_platforms)
{
	Controller c;
	ASSERT_THROWS(c.createStation("Kiev", -5),
		Messages::CountPlatformsMustBePositive
		);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_route_negative_id)
{
	Controller c;
	ASSERT_THROWS(c.createRoute(-50),
		Messages::NegativeID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_add_schedule_to_route_time_is_not_Valid)
{
	Controller c;
	c.createStation("Kiev", 15);
	c.createRoute(14);

	ASSERT_THROWS(c.addScheduleToRoute("-05:00", "07:10", "Kiev", 14),
		Messages::TimeIsNotValid
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_train_negative_id)
{
	Controller c;
	ASSERT_THROWS(c.createTrain(-5, 75),
		Messages::NegativeID
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_create_train_negative_count_passengers)
{
	Controller c;
	ASSERT_THROWS(c.createTrain(45, -5),
		Messages::NegativeCountPassengers
	);
}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_print_five_station_with_max_count_route_few_stations)
{
	Controller c;
	c.createStation("Poltava", 3);
	c.createStation("Kharkov", 2);
	c.createRoute(79);
	
	c.addScheduleToRoute("10:45", "10:55", "Poltava", 79);
	c.addScheduleToRoute("21:00", "21:10", "Kharkov", 79);

	ASSERT_THROWS(c.fiveStationWithMaxCountRoute(),
		Messages::FewStations
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_running_Train_on_route_train_must_be)
{
	Controller c;
	c.createRoute(33);

	ASSERT_THROWS(c.runningTrainOnRoute(33, 1349),
		Messages::TrainMustBe
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST(test_running_Train_on_route_route_must_be)
{
	Controller c;
	c.createTrain(1349, 30);

	ASSERT_THROWS(c.runningTrainOnRoute(19, 1349),
		Messages::RouteMustBe
	);
}
