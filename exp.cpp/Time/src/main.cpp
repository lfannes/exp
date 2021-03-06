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
	int time = 240;

	void print() const
	{
		int h = time/60;
		int m = time%60;
		cout << "Titanfall 2\n" << name << "\t" << "uren: " << h << "  minuten: " << m << "\t" << (started ? "\033[1m\033[32mstarted\033[0m" : "\033[1m\033[31mstopped\033[0m") << endl;
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
	void controleDay(auto &now_c, auto &now)
	{
		days = now_c / 86400;
		if (x == 1)
		{
			previous = days;
			x--;
		}

		if (previous != days)
		{
			reset();
			previous = days;
		}
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
			cout << timer.name << ": reset" << endl;
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
					std::cout << "\033[31mUnknown user " << name << "\033[0m" << std::endl;	
					for(auto timer : timers_)
					{
						timer.print();
					}	
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
				else if (str == "time")
				{
					cout << selected_timer_->name << ": " << 240 - selected_timer_->time << endl;
				}
				else
				{
					const char *begin = str.c_str();
					const char *end = begin+str.size();
					char *tot_hier_ok;
					long mins = std::strtol(begin, &tot_hier_ok, 10);
					if (tot_hier_ok != end)
					{
						cout << "\033[31m" << selected_timer_->name << ": " << str << " niet uitvoerbaar\033[0m" << endl;
						change_state_(State::Idle);
					}
					else
					{
						selected_timer_->time += mins;
						change_state_(State::Idle);						
					}
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
	int previous;
	int x = 1;
	int days;
};

int main()
{
	StateMachine sm;

	auto clock = [&]()
	{
		for (;true;)
		{
			std::this_thread::sleep_for(std::chrono::minutes(1));
			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			std::time_t now_c = std::chrono::system_clock::to_time_t(now);
			sm.process(1);
			sm.controleDay(now_c, now);
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
