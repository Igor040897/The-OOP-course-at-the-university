#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "time.hpp"
#include <memory>
#include <set>
#include <unordered_map>
#include <map>
#include <functional>  
#include <sstream>
#include <iterator> 

class Station;
class TrainScheduleltem;
class Route;
class Train;

class Controller
{
public:

	Controller();
	~Controller();
	
	Controller(const Controller &) = delete;
	Controller & operator = (const Controller &) = delete;

	void createStation(std::string const & _name, int _platforms);
	void createRoute(int _ID);
	void createTrain(int _id, int _countPassengers);
	void runningTrainOnRoute(int _idRoute, int _idTrain);

	void addScheduleToRoute(Time const & _arrival, Time const & _departure, std::string const & _nameStation, int _idRoute);
	std::stringstream const fiveStationWithMaxCountRoute() const;//сортуЇ по к≥лькост≥ маршрут≥в а пот≥м по назв≥ станц≥њ по алфав≥ту з к≥нц€
	std::stringstream const fiveRouteWithTheLongestTravelTime() const;
	std::stringstream const couplesStationInvolvingMoreThanTwoRoutes()const;
	std::stringstream const stationsWithoutRoute()const;
	std::stringstream const notEnoughPlatforms()const;

private:

	int countTrainAtGivenTime(std::vector<TrainScheduleltem> const & schedulrOneStation, Time const & _arrival)const;

	std::set<std::unique_ptr<TrainScheduleltem>> m_trainScheduleltem;
	std::unordered_map<std::string, std::unique_ptr<Station>> m_stations;
	std::unordered_map<int, std::unique_ptr<Route>> m_routes;
	std::unordered_map<int, std::unique_ptr<Train>> m_trains;

};

#endif //  _CONTROLLER_HPP_
