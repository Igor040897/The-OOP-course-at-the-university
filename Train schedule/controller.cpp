#include "Controller.hpp"

#include "Station.hpp"
#include "Route.hpp"
#include "Train.hpp"
#include "TrainScheduleItem.hpp"
#include "messages.hpp"
#include <algorithm>

Controller::Controller() = default;

Controller::~Controller() = default;

void Controller::createStation(std::string const & _name, int _platforms)
{
	std::unique_ptr<Station> station(new Station(_name, _platforms));
	m_stations[_name] = std::move(station);
}

void Controller::createRoute(int _ID)
{
	std::unique_ptr<Route> route(new Route(_ID));
	m_routes[_ID] = std::move(route);
}

void Controller::createTrain(int _id, int _countPassengers)
{
	std::unique_ptr<Train> train(new Train(_id, _countPassengers));
	m_trains[_id] = std::move(train);
}

void Controller::runningTrainOnRoute(int _idRoute, int _idTrain)
{
	if(!m_trains.count(_idTrain)) {
		throw std::logic_error(Messages::TrainMustBe);
	}
	if (!m_routes.count(_idRoute)) {
		throw std::logic_error(Messages::RouteMustBe);
	}
	auto itTrain = m_trains.find(_idTrain);
	auto itRoute = m_routes.find(_idRoute);
	itTrain->second->setRoute(*itRoute->second);
}

void Controller::addScheduleToRoute(Time const & _arrival, Time const & _departure, std::string const & _nameStation, int _idRoute)
{
	if (_nameStation.empty()) {
		throw std::logic_error(Messages::NameEmpty);
	}
	if (_idRoute < 0) {
		throw std::logic_error(Messages::NegativeID);
	}
	if (!m_stations.count(_nameStation)) {
		throw std::logic_error(Messages::StationMustBe);
	}
	if (!m_routes.count(_idRoute)) {
		throw std::logic_error(Messages::RouteMustBe);
	}
	auto itUMRoute = m_routes.find(_idRoute);
	auto itUMStation = m_stations.find(_nameStation);
	std::unique_ptr<TrainScheduleltem> schedule(new TrainScheduleltem(_arrival, _departure, *itUMStation->second));
	itUMRoute->second->addSchedule(*schedule);
	m_trainScheduleltem.insert(std::move(schedule));
}

std::stringstream const Controller::fiveStationWithMaxCountRoute() const
{
	std::unordered_map<std::string, int> countRouteOnOneStation;
	for (auto const & route : m_routes) {
		for(TrainScheduleltem const * schedule : route.second->schedule()){
			if (countRouteOnOneStation.count(schedule->getStation().getName()) == 1) {
				countRouteOnOneStation[schedule->getStation().getName()]++;
			}
			else countRouteOnOneStation[schedule->getStation().getName()] = 1;
		}
	}

	if (countRouteOnOneStation.size() < 5) {
		throw std::logic_error(Messages::FewStations);
	}

	std::set < std::pair<int, std::string>> stations;
	for (auto _countRouteOnOneStation : countRouteOnOneStation) {
		stations.insert(std::make_pair(_countRouteOnOneStation.second, _countRouteOnOneStation.first));
	}

	std::stringstream ss;
	auto itStation = stations.end();
	for (int i = 0; i < 5; i++) {
		itStation--;
		ss << itStation->second << '=' << itStation->first;
		(i != 4) ? ss << "; ": ss << '\0';
	};
	return ss;
}

std::stringstream const Controller::fiveRouteWithTheLongestTravelTime() const
{
	std::map<Time const, Route const, std::greater<Time>> routeWithDurationOfTrip;
	for (auto const & route : m_routes) {
		routeWithDurationOfTrip.insert(std::make_pair(
			(*route.second->scheduleRBegin())->getAriival() - (*route.second->scheduleBegin())->getAriival(), (*route.second)));
	}
	if (routeWithDurationOfTrip.size() < 5) {
		throw std::logic_error(Messages::FewRoute);
	}
	std::stringstream ss;
	auto itRoute = routeWithDurationOfTrip.begin();
	for (int i = 0; i < 5; i++) {
		ss << "Number of the route = " << itRoute->second.getID() 
		   << ": Start = " << (*itRoute->second.scheduleBegin())->getStation().getName()
		   << "; Finish = " << (*itRoute->second.scheduleRBegin())->getStation().getName() << "; "
		   << "the duration of the road : " << itRoute->first.getHour() << "/" << itRoute->first.getMinute();
		(i != 4) ? ss << "; " : ss << '\0';
		itRoute++;
	};
	return ss;
}

std::stringstream const Controller::couplesStationInvolvingMoreThanTwoRoutes() const
{
	std::vector<Station> couple(2);
	std::set<std::pair<Station, Station>> coupleWithMoreThanTwoRoutes;
	int advance = 1;
	std::for_each(m_routes.begin(), m_routes.end(), [&](auto const & _pRoute) {
		auto itSchedule = _pRoute.second->scheduleBegin();
		while (itSchedule != _pRoute.second->scheduleEnd()) {
			do {
				couple[0] = (*itSchedule)->getStation();
				std::advance(itSchedule, 1);
				if (itSchedule == _pRoute.second->scheduleEnd()) {
					break;
				}
				couple[1] = (*itSchedule)->getStation();
			} 
			while (coupleWithMoreThanTwoRoutes.count(std::make_pair(couple[0], couple[1])) == 1); 

			auto itRouteToAdvance = m_routes.begin();
			std::advance(itRouteToAdvance, advance);
			while (itRouteToAdvance != m_routes.end()) {
				auto itCouple = std::find_end((*itRouteToAdvance).second->scheduleBegin(), 
					(*itRouteToAdvance).second->scheduleEnd(), couple.begin(), couple.end(),
					[](TrainScheduleltem const *_schedule, Station const & _station) {
					return _schedule->getStation() == _station;
				});
				if (itCouple != (*itRouteToAdvance).second->scheduleEnd()) {
					if (coupleWithMoreThanTwoRoutes.count(std::make_pair(couple[0], couple[1])) == 0) {
						coupleWithMoreThanTwoRoutes.insert(std::make_pair(couple[0], couple[1]));
					}
				}
				itRouteToAdvance++;
			}
		}
		advance++;
	});

	if (coupleWithMoreThanTwoRoutes.empty()) {
		throw std::logic_error(Messages::NoIntersectionsOfRoutes);
	}

	std::stringstream  ss;
	auto itStations = coupleWithMoreThanTwoRoutes.begin();
	for (int i = 0; i < (int)coupleWithMoreThanTwoRoutes.size(); i++) {
	ss << "Flight: " << itStations->first.getName() << " - " << itStations->second.getName();
	itStations++;
	(itStations != coupleWithMoreThanTwoRoutes.end()) ? ss << "; " : ss << '\0';
	};
	return ss;
}

std::stringstream const Controller::stationsWithoutRoute() const
{
	std::set<Station> stationsWithoutRoute;
	for ( auto const & _station : m_stations) {
		auto itRouteWithStation = std::find_if(m_routes.begin(), m_routes.end(), 
			[&](auto const & _route){
			return _route.second->hasStation(*_station.second);
		});
		if (itRouteWithStation == m_routes.end()) {
			stationsWithoutRoute.insert(*_station.second);
		}
	}
	if (stationsWithoutRoute.empty()) {
		throw std::logic_error(Messages::AllStationsWithRoutes);
	}

	std::stringstream ss;
	ss << "Stations: ";
	auto itStation = stationsWithoutRoute.begin();
	for (int i = 0; i < (int)stationsWithoutRoute.size(); i++) {
		ss << itStation->getName();
		itStation++;
		(itStation != stationsWithoutRoute.end()) ? ss << "; " : ss << '\0';
	}
	return ss;
}

std::stringstream const Controller::notEnoughPlatforms() const
{
	std::map<Station, int> loadingPlatforms;
	
	for (auto const & _station : m_stations) {
		std::vector<TrainScheduleltem> vec;
		std::for_each(m_trainScheduleltem.begin(), m_trainScheduleltem.end(),
			[&](auto const &_pSchedule) {
			if (_pSchedule->getStation() == *_station.second) {
				vec.push_back(*_pSchedule);
			}
		});
		std::set<int, std::greater<int>> maxCount;
		std::for_each(vec.begin(), vec.end(), [&](TrainScheduleltem _two) {
			maxCount.insert(countTrainAtGivenTime(vec, _two.getAriival()));
		});
		if (!maxCount.empty()) {
			if(*maxCount.begin()>vec.begin()->getStation().getSizePlatform())
				loadingPlatforms[*_station.second] = *maxCount.begin();
		}
	}
	if (loadingPlatforms.empty()) {
		throw std::logic_error(Messages::NotEnoughFreePlatforms);
	}

	std::stringstream ss;
	auto & itStation = loadingPlatforms.begin();
	for (int i = 0; i < (int)loadingPlatforms.size(); i++) {
		ss << itStation->first.getName();
		itStation++;
		(itStation != loadingPlatforms.end()) ? ss << "; " : ss << '\0';
	}
	return ss;
}

int Controller::countTrainAtGivenTime(std::vector<TrainScheduleltem> const & schedulrOneStation, Time const & _arrival)const
{
	int count = 0;
	count = std::count_if(schedulrOneStation.begin(), schedulrOneStation.end(), 
		[&](TrainScheduleltem _schedule) {
		return ((_arrival >= _schedule.getAriival()) && (_arrival <= _schedule.getDeparture()));
	});
	return count;
}


