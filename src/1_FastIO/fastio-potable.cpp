#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")

#include <stdio.h>

namespace
{
class FastIn {
public:
	constexpr static int BUFFER_MAX = 1048576;
	char buf[BUFFER_MAX + 1];
	int pos;
	FILE* fp;
	int pl;
	int eof;

	// Customize yourselfs
	static inline bool isEmpty(char x){
		return x<=32;
	}

private:
	FastIn() {
		clear();
	}
	~FastIn() {
		//flush();
	}
	void clear() {
		pos = BUFFER_MAX;
		pl = BUFFER_MAX;
		fp = stdin;
		eof = 0;
	}
	void read_buffer() {
		if (eof)return;
		if (feof(fp)) { eof = 1; return; }
		pl = fread(buf, sizeof(char), BUFFER_MAX, fp);
	}
	char __getchar() {
		if (pos == pl) {
			pos = 0;
			read_buffer();
			if (eof)return -1;
		}
		return buf[pos++];
	}
	int __nextint() {
		int res = 0;
		char c;
		bool minus = false;
		do {
			c = getchar();
			if (eof)return 0;
			if (c == '-')minus = true;
		} while (c < '0' || c>'9');
		res = c - '0';
		while (1) {
			c = getchar();
			if (eof)break;
			if (c < '0' || c>'9')break;
			res = (res * 10) + c - '0';
		}
		return minus ? -res : res;
	}

	int __nextstring(char* x) {
		int i = 0;
		char c;
		do {
			c = getchar();
			if (eof)return 0;
		} while (isEmpty(c));
		x[i++] = c;
		while (1) {
			c = getchar();
			if (eof)break;
			if (isEmpty(c))break;
			x[i++] = c;
		}
		x[i] = 0;
		return i;
	}

public:
	static FastIn& Get() {
		static FastIn instance;
		return instance;
	}
	static void setfp(FILE* _fp) {
		Get().fp = _fp;
	}
	static char getchar() {
		return Get().__getchar();
	}
	static int nextint() {
		return Get().__nextint();
	}
	static int nextstring(char* x) {
		return Get().__nextstring(x);
	}
};

class FastOut {
public:
	constexpr static int BUFFER_MAX = 1048576;
	char buf[BUFFER_MAX + 1];
	int pos;
	FILE* fp;
	
	// Customize yourselfs
	static inline bool isEmpty(char x){
		return x<=32;
	}

private:
	FastOut() {
		clear();
	}
	~FastOut() {
		flush();
	}
	void clear() {
		pos = 0;
		fp = stdout;
	}
	void flush() {
		if (pos > 0) {
			fwrite(buf, 1, pos, fp);
			pos = 0;
		}
	}
	void __putchar(char x) {
		if (pos == BUFFER_MAX) {
			flush();
		}
		buf[pos++] = x;
	}
	void __nextint(int x, char eow = ' ') {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x == 0) {
			putchar('0');
		}
		else {
			char xx[20];
			int xl = 0;
			while (x > 0) {
				xx[xl++] = x % 10 + '0';
				x /= 10;
			}
			while (xl--) {
				putchar(xx[xl]);
			}
		}
		if (eow > 0)
			putchar(eow);
	}
	void __nextstring(char* x, char eow = ' ', int xl = -1)
	{
		for(int i=0; (xl>=0 && i<xl) || !isEmpty(x[i]); i++)
		{
			putchar(x[i]);
		}
		if (eow > 0)
			putchar(eow);
	}

public:
	static FastOut& Get(){
		static FastOut instance;
		return instance;
	}
	static void setfp(FILE* _fp) {
		Get().fp = _fp;
	}
	static void putchar(char c)
	{
		Get().__putchar(c);
	}
	static void nextint(int x, char eow = ' ')
	{
		Get().__nextint(x, eow);
	}
	static void nextstring(char* x, char eow = ' ', int xl = -1)
	{
		Get().__nextstring(x, eow, xl);
	}
};
}