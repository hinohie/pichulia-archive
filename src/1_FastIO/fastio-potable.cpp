#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")

class FastIn {
public:
	const static int BUFFER_MAX = 1048576;
	static char buf[BUFFER_MAX + 1];
	static int pos;
	static FILE* fp;
	static int pl;
	static int eof;
	FastIn() {
		clear();
	}
	static void clear() {
		pos = BUFFER_MAX;
		pl = BUFFER_MAX;
		fp = stdin;
		eof = 0;
	}
	static void setfp(FILE* _fp) {
		fp = _fp;
	}
	static void read_buffer() {
		if (eof)return;
		if (feof(fp)) { eof = 1; return; }
		pl = fread(buf, sizeof(char), BUFFER_MAX, fp);
	}
	static char getchar() {
		if (pos == pl) {
			pos = 0;
			read_buffer();
			if (eof)return -1;
		}
		return buf[pos++];
	}
	static int nextint() {
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

	static void nextstring(char* x) {
		register int i = 0;
		char c;
		do {
			c = getchar();
			if (eof)return;
		} while (c < 'a' || c>'z');
		x[i++] = c;
		while (1) {
			c = getchar();
			if (eof)break;
			if (c < 'a' || c>'z')break;
			x[i++] = c;
		}
		x[i] = 0;
	}

	static void nextstring(char* x, int& xl) {
		xl = 0;
		char c;
		do {
			c = getchar();
			if (eof)return;
		} while (c < 'a' || c>'z');
		x[xl++] = c;
		while (1) {
			c = getchar();
			if (eof)break;
			if (c < 'a' || c>'z')break;
			x[xl++] = c;
		}
		x[xl] = 0;
	}
};
char FastIn::buf[FastIn::BUFFER_MAX + 1];
int FastIn::pos = FastIn::BUFFER_MAX;
FILE* FastIn::fp = stdin;
int FastIn::pl = FastIn::BUFFER_MAX;
int FastIn::eof = 0;

class FastOut {
public:
	const static int BUFFER_MAX = 1048576;
	static char buf[BUFFER_MAX + 1];
	static int pos;
	static FILE* fp;
	FastOut() {
		clear();
	}
	~FastOut() {
		flush();
	}
	static void clear() {
		pos = 0;
		fp = stdout;
	}
	static void setfp(FILE* _fp) {
		fp = _fp;
	}
	static void flush() {
		if (pos > 0) {
			fwrite(buf, 1, pos, fp);
			pos = 0;
		}
	}
	static void __putchar(char x) {
		if (pos == BUFFER_MAX) {
			flush();
		}
		buf[pos++] = x;
	}
	static void nextint(int x, char eow = ' ') {
		if (x < 0) {
			__putchar('-');
			x = -x;
		}
		if (x == 0) {
			__putchar('0');
		}
		else {
			char xx[20];
			int xl = 0;
			while (x > 0) {
				xx[xl++] = x % 10 + '0';
				x /= 10;
			}
			while (xl--) {
				__putchar(xx[xl]);
			}
		}
		if (eow > 0)
			__putchar(eow);
	}
};
char FastOut::buf[FastOut::BUFFER_MAX + 1];
int FastOut::pos = 0;
FILE* FastOut::fp = stdout;
