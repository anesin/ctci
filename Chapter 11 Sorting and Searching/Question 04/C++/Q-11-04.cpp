// Q-11-04
//   Imagine you have a 20 GB file with one string per line.
//   Explain how you would sort the file.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // sort
#include <cstdio>  // remove

using namespace std;


void split_file(vector<fstream *> &files, fstream &src, size_t line_num)
{
	src.seekg(0);  // rewind
	for (int i = 1; src.eof() == false; ++i) {
		vector<string> buf;
		string s;
		int j = line_num;
		while (--j >= 0 && src.eof() == false) {
			getline(src, s);
			if (s.length() > 0)
				buf.push_back(s);
		}

		if (buf.size() == 0)
			break;

		sort(buf.begin(), buf.end());

		string name = to_string(i) + ".tmp";
		fstream *f = new fstream(name, ios::in|ios::out);
		for (auto line : buf)
			*f << line << endl;
		f->seekg(0);
		files.push_back(f);

		buf.clear();
	}
}

void delete_files(vector<fstream *> &files)
{
	for (auto f : files) {
		f->close();
		delete f;
	}

	int i = files.size();
	while (--i >= 0) {
		string name = to_string(i) + ".tmp";
		remove(name.c_str());
	}
}

bool all_eof(const vector<fstream *> &files)
{
	for (auto f : files) {
		if (f && f->eof() == false)
			return false;
	}
	return true;
}

int min_element(const vector<string> &strings)
{
	int min = -1;
	int i = -1;
	int n = strings.size();
	while (++i < n) {
		if (min < 0) {
			if (strings[i].length() > 0)
				min = i;
			continue;
		}

		if (strings[i] < strings[min])
			min = i;
	}

	return min;
}

void external_sort(fstream &src, fstream &dst, size_t line_num)
{
	vector<fstream *> files;
	split_file(files, src, line_num);

	vector<string> strings;
	strings.reserve(files.size());
	string s;
	for (auto f : files) {
		getline(*f, s);
		strings.push_back(s);
	}

	dst.seekg(0);  // rewind
	int min = min_element(strings);
	while (min >= 0 && all_eof(files) == false) {
		dst << strings[min] << endl;
		if (files[min]->eof()) {
			strings[min] = "";
		}
		else {
			getline(*files[min], s);
			strings[min] = s;
		}
		min = min_element(strings);
	}

	delete_files(files);
}




void make_file(fstream &file, const char *name, int line_num)
{
	file.open(name, ios::in|ios::out);
	cout << file.rdstate() << endl;
	char ch = 'z';
	int count = 1;
	while (--line_num >= 0) {
		string str = string(count, ch--);
		file << str << endl;
		if (ch < 'a') {
			ch = 'z';
			++count;
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	static const int kLineNum = 1000;

	fstream file;
	make_file(file, "20GB.txt", kLineNum * 10);
	fstream result("result.txt", ios::out);
	external_sort(file, result, kLineNum);
	file.close();
	result.close();

	return 0;
}
