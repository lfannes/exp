#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <cassert>

using namespace std;

struct PersonTimer
{
	PersonTimer(string name): name(name){}

	string name;
	bool started = false;
	int time = 180;

	void print() const
	{
		cout << name << "\t" << time << "\t" << (started ? "started" : "stopped") << endl;
	}
};

class StateMachine
{
public:
	StateMachine()
	{
		timers_.push_back(PersonTimer("Lander"));
		timers_.push_back(PersonTimer("Tibe"));
		timers_.push_back(PersonTimer("Tuur"));
		timers_.push_back(PersonTimer("Siem"));
		change_state_(State::Idle);
	}
	void process(int mins)
	{
		std::lock_guard<std::mutex> lock(mutex_);

		minutes_ += mins;
		switch (state_)
		{
			case State::Idle:
			{
				change_state_(State::UpdateStartedTimers);
			}
			break;
		}
	}
	void reset()
	{
		for(auto &timer : timers_)
		{
			timer.time = 180;
			timer.started = false;
		}
	} 
	void process(std::string str)
	{
		std::lock_guard<std::mutex> lock(mutex_);

		switch (state_)
		{
			case State::Idle:
			{
				const std::string &name = str;
				assert(selected_timer_ == nullptr);
				for(auto &timer : timers_)
				{
					if (timer.name == name)
					{
						selected_timer_ = &timer;
						break;
					}
				}
				if (!selected_timer_)
				{
					std::cout << "Unknown user " << name << std::endl;		
					break;		
				}
				change_state_(State::Selected);
			}
			break;

			case State::Selected:
			{
				if (false) {}
				else if (str == "start")
				{
					change_state_(State::StartTimer);
				}
				else if (str == "stop")
				{
					change_state_(State::StopTimer);
				}
				else
				{
					int mins = std::stoi(str);
					selected_timer_->time += mins;
					change_state_(State::Idle);
				}
			}
			break;
		}
	}
private:
	enum class State
	{
		Init, Idle, UpdateStartedTimers, Selected, StartTimer, StopTimer 
	};

	void change_state_(State newState)
	{
		if (state_ == newState)
			return;

		//exit
		switch(state_)
		{
			case State::UpdateStartedTimers:
			minutes_ = 0;
			break;
		}

		state_ = newState;
		
		//enter
		switch(state_)
		{
			case State::Idle:
			selected_timer_ = nullptr;
			cout << endl;
			for (auto timer : timers_)
				timer.print();
			break;

			case State::UpdateStartedTimers:
			for (auto &timer : timers_)
				if (timer.started)
					timer.time -= minutes_;
			change_state_(State::Idle);
			break;

			case State::Selected:
			cout << "Selected ";
			selected_timer_->print();
			break;

			case State::StartTimer:
			selected_timer_->started = true;
			change_state_(State::Idle);
			break;

			case State::StopTimer:
			selected_timer_->started = false;
			change_state_(State::Idle);
			break;
		}
	}

	std::mutex mutex_;
	State state_ = State::Init;
	PersonTimer *selected_timer_ = nullptr;
	int minutes_ = 0;
	std::vector<PersonTimer> timers_;
};

int main()
{
	StateMachine sm;

	auto clock = [&sm]()
	{
		auto now = std::chrono::system_clock::now();;
		auto now_c = std::chrono::system_clock::to_time_t(now);
		auto m_since_1970 = now_c / 60;
		auto u_since_1970 = m_since_1970 / 60;
		auto d_since_1970 = u_since_1970 / 24;
		auto previous = d_since_1970;
		for (;true;)
		{
			std::this_thread::sleep_for(std::chrono::minutes(1));
			sm.process(1);
			if (d_since_1970 != previous)
			{
				sm.reset();
				previous = d_since_1970;
			}
		}
	};

	std::thread clock_thread(clock);

	for (;true;)
	{
		std::string str;
		std::cin >> str;
		sm.process(str);
	}
	return 0;
}