#include <iostream>
#include <string>

using namespace std;

struct PersonTimer
{
	PersonTimer(string name)
	:name(name)
	{

	}

	string name;
	bool started = false;
	int time = 180;
};

class StateMachine
{
public:
	StateMachine()
	{
		change_state_(State::Idle);
	}
	void process(int mins)
	{
		const int &minutes = mins;
		switch (state_)
		{
			case State::Idle:
			{
				if (false) {}
				else if (lander_.started == true) selected_timer_ = &lander_;
				else if (tibe_.started == true) selected_timer_ = &tibe_;
				else if (tuur_.started == true) selected_timer_ = &tuur_;
				else if (siem_.started == true) selected_timer_ = &siem_;
				else
				{
					std::cout << "No body is active" << std::endl;
					return;
				}
				change_state_(State::UpdateStartedTimers);
			}
			break;
		}
	}
	void process(std::string str)
	{
		switch (state_)
		{
			case State::Idle:
			{
				const std::string &name = str;
				if (false) {}
				else if (name == "lander") selected_timer_ = &lander_;
				else if (name == "tibe") selected_timer_ = &tibe_;
				else if (name == "tuur") selected_timer_ = &tuur_;
				else if (name == "siem") selected_timer_ = &siem_;
				else
				{
					std::cout << "Unknown user " << name << std::endl;
					return;
				}
				change_state_(State::Selected);
			}
			break;

			case State::Selected:
			{
				const std::string &command = str;
				if (false) {}
				else if (command == "update")
				{
					change_state_(State::UpdateSelectedTimer);
				}
				else if (command == "start")
				{
					change_state_(State::StartTimer);
				}
				else if (command == "stop")
				{
					change_state_(State::StopTimer);
				}
				else
				{
					std::cout << "Unknown command " << command << std::endl;
					return;
				}
			}
			break;

		}

	}
private:
	enum class State
	{
		Init, Idle, UpdateStartedTimers, Selected, UpdateSelectedTimer, StartTimer, StopTimer 
	};

	void change_state_(State newState)
	{
		if (state_ == newState)
			return;

		//exit
		switch(state_)
		{
		}

		state_ = newState;
		
		//enter
		switch(state_)
		{
			case State::Idle:
			selected_timer_ = nullptr;
			cout << lander_.name << "\t" << lander_.time << "\t" << (lander_.started ? "started" : "stopped") << endl;
			cout << tibe_.name << "\t" << tibe_.time << "\t" << (tibe_.started ? "started" : "stopped") << endl;
			break;

			case State::Selected:
			cout << "Selected " << selected_timer_->name << endl;
			break;

			case State::StartTimer:
			selected_timer_->started = true;
			change_state_(State::Idle);
			break;
			case State::StopTimer:
			selected_timer_->started = false;
			change_state_(State::Idle);
			break;

			case State::UpdateStartedTimers:
			selected_timer_->time -= 1;
			cout << selected_timer_->name << "\t" << selected_timer_->time << endl;
			selected_timer_ = nullptr;
			change_state_(State::Idle);
			break;
		}
	}

	State state_ = State::Init;
	PersonTimer lander_{"Lander"};
	PersonTimer tibe_{"Tibe"};
	PersonTimer tuur_{"Tuur"};
	PersonTimer siem_{"Siem"};
	PersonTimer *selected_timer_ = nullptr;
};

int main()
{
	StateMachine sm;
	//Scenario Lander start met gamen
	//* Inloggen
	//** lander<enter>
	//* Aanduiden start gamen
	//** start<enter>
	//* Uitloggen vanzelf
	sm.process("lander");
	sm.process("start");
	sm.process(1);
	sm.process(1);
	sm.process(1);
	sm.process(1);
	sm.process("lander");
	sm.process("stop");

	sm.process(1);
	sm.process(1);

	sm.process("tibe");
	sm.process("start");

	sm.process(1);
	sm.process(1);
	sm.process(1);
	sm.process(1);
	sm.process(1);
	sm.process(1);

	sm.process("tibe");
	sm.process("stop");
	return 0;
}