#include <stdio.h>
#include <assert.h>

#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

using std::cout;
using std::endl;
using std::vector;

int get_next_int(const char *input)
{
	static int index;
	int n = 0;

	while (input[index] && input[index] != '\n' && input[index] != ',') {
		n *= 10;
		n += input[index] - '0';
		index++;
	}

	while (input[index] == '\n' || input[index] == ',')
		index++;

	// The end of input
	if (!input[index])
		index = 0;

	return n;
}

struct Mountain {

	Mountain() : l(0), r(0), h(0)
	{}
	Mountain(int _l, int _r, int _h) : l(_l), r(_r), h(_h)
	{}

	bool operator< (const Mountain& rt)  
	{  
		return this->l < rt.l;  
	}

	int l;
	int r;
	int h;
};

bool Compare(const Mountain &left, const Mountain &right)  
{  
	return left.l < right.l;
}

void print_mountains(const vector<Mountain> &mountains)
{
	cout << "mountains:" << endl;
	for (int i = 0; i < mountains.size(); i++) {
		cout << "[" << i << "]=" << mountains[i].l << ","
			<< mountains[i].r << "," << mountains[i].h << endl;
	}
}

void merge(vector<Mountain> &mountains, int index)
{
	if (index == mountains.size() - 1)
		return;
	if (mountains[index].r <= mountains[index + 1].l)
		return merge(mountains, index + 1);

	Mountain m1, m2;

	m1 = mountains[index];
	m2 = mountains[index + 1];

 	int l1, l2, r1, r2, h1, h2;

	l1 = m1.l;
	r1 = m1.r;
	h1 = m1.h;

	l2 = m2.l;
	r2 = m2.r;
	h2 = m2.h;

	if (r2 < r1) {
		if (l1 < l2) {
			if (h1 < h2) {
				mountains[index] = Mountain(l1, l2, h1);
				mountains[index + 1] = Mountain(l2, r2, h2);
				mountains.push_back(Mountain(r2, r1, h1));
			} else {
				// m2 is useless
				mountains.erase(mountains.begin() + index + 1);
			}
		} else {
			// l1 == l2
			int h = h1 < h2 ? h2 : h1;
			mountains[index] = Mountain(l1, r2, h);
			mountains[index + 1] = Mountain(r2, r1, h1);
		}
	} else {
		if (l1 == l2) {
			if (h1 <= h2) {
				mountains.erase(mountains.begin() + index);
			} else {
				mountains[index + 1] = Mountain(r1, r2, h2);
			}
		} else {
			if (h1 <= h2) {
				mountains[index] = Mountain(l1, l2, h1);
			} else {
				mountains[index + 1] = Mountain(r1, r2, h2);
			}
		}
	}

	std::sort(mountains.begin(), mountains.end(), Compare);
	merge(mountains, index);
}

int resolve(const char* input)
{
	int t = get_next_int(input);

	vector<Mountain> mountains(t);

	int l, r, h;
	int m = 0;

	for (int i = 0; i < t; i++)
	{
		l = get_next_int(input);
		r = get_next_int(input);
		h = get_next_int(input);
		m = m < r ? r : m;
		mountains[i] = Mountain(l, r, h);
	}

	std::sort(mountains.begin(), mountains.end(), Compare);

	merge(mountains, 0);

	// print_mountains(mountains);

	int ans = m;

	if (mountains.size() > 0)
		ans += mountains[0].h;

	for (int i = 1; i < mountains.size(); i++)
	{
		if (mountains[i].l == mountains[i - 1].r)
			ans += abs(mountains[i].h - mountains[i - 1].h);
		else
			ans += mountains[i - 1].h + mountains[i].h;
	}
	ans += mountains.back().h;

    return ans;
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
