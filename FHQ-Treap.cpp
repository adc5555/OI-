#include <bits/stdc++.h>

namespace OI {
	using std::pair;
	struct Treap {
		Treap *l, *r;
		int val, siz, key; //权值，大小，堆键值
		void maintain() {
			siz = 1 + (l == NULL ? 0 : l->siz) + (r == NULL ? 0 : r->siz);
		}
		Treap(int v) {
			val = v;
			siz = 1;
			key = rand();
			l = r = NULL;
		}
		int size() {
			if (this != NULL)
				return siz;
			else
				return 0;
		}
	} *root;
	int size(Treap *x) {
		return x ? x->siz : 0;
	}
	typedef pair<Treap *, Treap *> DTreap;
	Treap *merge(Treap *a, Treap *b) {
		if (a == NULL)
			return b;
		if (b == NULL)
			return a;
		if (a->key < b->key) {
			a->r = merge(a->r, b);
			a->maintain();
			return a;
		} else {
			b->l = merge(a, b->l);
			b->maintain();
			return b;
		}
	}
	DTreap splitK(Treap *o, int k) { //按照排名分裂
		if (!o)
			return DTreap(NULL, NULL);
		DTreap ret;
		if (size(o->l) >= k) {
			ret = splitK(o->l, k);
			o->l = ret.second;
			o->maintain();
			ret.second = o;
		} else {
			ret = splitK(o->r, k - size(o->l) - 1);
			o->r = ret.first;
			o->maintain();
			ret.first = o;
		}
		return ret;
	}

	int Getkth(Treap *o, int k) { //按值查排名
		if (!o)
			return 0;
		return (o->val >= k) ? Getkth(o->l, k) : Getkth(o->r, k) + size(o->l) + 1;
	}

	int Findkth(Treap *root, int k) {
		DTreap x = splitK(root, k - 1);
		DTreap y = splitK(x.second, 1);
		Treap *ans = y.first;
		root = merge(merge(x.first, ans), y.second);
		return ans ? ans->val : 0;
	}

	void Insert(Treap *&root, int val) {
		int k = Getkth(root, val);
		DTreap x = splitK(root, k);
		Treap *o = new Treap(val);
		root = merge(merge(x.first, o), x.second);
	}
	void Delete(Treap *&root, int val) {
		int k = Getkth(root, val);
		DTreap x = splitK(root, k);
		DTreap y = splitK(x.second, 1);
		root = merge(x.first, y.second);
	}
};
using namespace OI;

int main() {
	srand(time(0));
	int n;
	scanf("%d", &n);
	while (n--) {
		int opt, x;
		scanf("%d%d", &opt, &x);
		switch (opt) {
			case 1:
				Insert(root, x);
				break;
			case 2:
				Delete(root, x);
				break;
			case 3:
				printf("%d\n", Getkth(root, x) + 1);
				break;
			case 4:
				printf("%d\n", Findkth(root, x));
				break;
			case 5:
				printf("%d\n", Findkth(root, Getkth(root, x)));
				break;
			case 6:
				printf("%d\n", Findkth(root, Getkth(root, x + 1) + 1));
				break;
		}
	}
}