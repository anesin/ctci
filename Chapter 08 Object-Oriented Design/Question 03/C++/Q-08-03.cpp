// Q-08-03.cpp
//    Design a musical jukebox using object-oriented principles.
//

#include "stdafx.h"
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;


typedef struct {
	int title;
	int artist;
	vector<unsigned char> data;
} Music;


class Player {
private:
	queue<const Music *> play_list_;
	bool playing_;

	recursive_mutex mutex_;

public:
	Player() : playing_(false) {}

	void clear() {
		lock_guard<recursive_mutex> lock(mutex_);
		playing_ = false;
		queue<const Music *> trash;
		play_list_.swap(trash);
	}

	void ready(const Music *music) {
		lock_guard<recursive_mutex> lock(mutex_);
		if (music)
			play_list_.push(music);
	}

	void play_all() {
		lock_guard<recursive_mutex> lock(mutex_);
		if (playing_ || play_list_.empty())
			return;

		char log[1024];
		_snprintf(log, sizeof(log), "[PLAY_ALL] size: %d\n", play_list_.size());
		cout << log;

		playing_ = true;
		while (playing_ && play_list_.empty() == false) {
			const Music *music = play_list_.front();
			play_list_.pop();
			if (music)
				play(*music);
		}
		playing_ = false;
	}

private:
	void play(const Music &music) {
		lock_guard<recursive_mutex> lock(mutex_);
		char log[1024];
		_snprintf(log, sizeof(log), "\"%d\", %d\n", music.title, music.artist);
		cout << log;
	}
};


class Jukebox {
private:
	vector<Music> music_list_;
	Player player_;

public:
	void update(vector<Music> &music_list) {
		music_list_.swap(music_list);
		player_.clear();
	}

	bool play(unsigned int index) {
		if (index >= music_list_.size())
			return false;

		char log[1024];
		_snprintf(log, sizeof(log), "ready %dth\n", index);
		cout << log;

		player_.ready(&music_list_[index]);
		thread t(&Player::play_all, &player_);
		t.join();
		return true;
	}

	const vector<Music> & music_list() {
		return music_list_;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	vector<Music> music_list;
	Music music;
	for (int i = 0; i < 100; ++i) {
		music.artist = 100 + i;
		music.title = 10000 + i;
		music_list.push_back(music);
	}

	Jukebox jukebox;
	jukebox.update(music_list);

	const static int kTestcase = 20;
	thread t[kTestcase];

	for (int j = 0; j < kTestcase; ++j)
		t[j] = thread(&Jukebox::play, &jukebox, j * 2);

	for (int k = 0; k < kTestcase; ++k)
		t[k].join();

	return 0;
}

