// Q-08-03.cpp
//    Design a musical jukebox using object-oriented principles.
//

#include "stdafx.h"
#include <vector>
#include <queue>
#include <string>
#include <iostream>

using namespace std;


typedef struct {
	int title;
	int artist;
	vector<unsigned char> data;
} Music;


class Player {
public:
	void play(const Music *music) const {
		cout << "Title: " << music->artist << endl;
		cout << "Artist: " << music->title << endl;
	}
};


class Jukebox {
private:
	vector<Music> music_list_;
	queue<const Music *> play_list_;
	Player player_;
	bool playing_;

public:
	Jukebox() : playing_(false) {}

	void update(vector<Music> &music_list) {
		music_list_.swap(music_list);
	}

	bool play(unsigned int index) {
		if (index >= music_list_.size())
			return false;
		cout << "ready " << index << "th" << endl;
		play_list_.push(&music_list_[index]);
		if (playing_ == false)
			play();
		return true;
	}

	const vector<Music> & music_list() {
		return music_list_;
	}

private:
	void play() {
		playing_ = true;
		while (play_list_.empty() == false) {
			const Music *music = play_list_.front();
			play_list_.pop();
			player_.play(music);
		}
		playing_ = false;
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

	for (int j = 0; j < 20; ++j)
 		jukebox.play(j * 2);

	return 0;
}

