template<typename T, typename U>
struct range_minimum_query {
	const T id;
	const function<T(T, T)> merge_function;
	const function<void(U&)> twice;
	const function<U(U)> half;
	range_minimum_query(T id):
		id(id),
		merge_function ([](T a, T b) {return min(a, b);}),
		twice ([](U& a) {}),
		half ([](U a) {return a;})
		{
		}
};
template<typename T, typename U>
struct range_maximum_query {
	const T id;
	const function<T(T, T)> merge_function;
	const function<void(U&)> twice;
	const function<U(U)> half;
	range_maximum_query(T id):
		id(id),
		merge_function ([](T a, T b) {return max(a, b);}),
		twice ([](U& a) {}),
		half ([](U a) {return a;})
		{
		}
};
template<typename T, typename U>
struct range_sum_query {
	const T id;
	const function<T(T, T)> merge_function;
	const function<void(U&)> twice;
	const function<U(U)> half;
	range_sum_query(T id = 0):
		id(id),
		merge_function ([](T a, T b) {return a + b;}),
		twice ([](U& a) {a *= 2;}),
		half ([](U a) {return a / 2;})
		{
		}
};
template<typename T, typename U>
struct range_update_query {
		const U id;
		const function<void(T&, U)> action;
		const function<void(U&, U)> composition;
	public:
		range_update_query(U id = 0):
			id(id),
			action ([](T& a, U b) {a = b;}),
			composition ([](U& a, U b) {a = b;})
			{
			}
};
template<typename T, typename U>
struct range_add_query {
		const U id;
		const function<void(T&, U)> action;
		const function<void(U&, U)> composition;
	public:
		range_add_query(U id = 0):
			id(id),
			action ([](T& a, U b) {a += b;}),
			composition ([](U& a, U b) {a += b;})
			{
			}
};
template<typename T, typename U>
class lazy_segment_tree {
	int sz;
	int Sz;
	int ht;
	vector<T> seg;
	vector<U> act;
	vector<bool> has_act;
	const function<T(T, T)> o;
	const function<void(T&, U)> oo;
	const function<void(U&, U)> ooo;
	const function<void(U&)> twice;
	const function<U(U)> half;
	const T tid;
	const U uid;
	
	public:
		lazy_segment_tree(
				int n,
				const function<T(T, T)> merge_function,
				const function<void(T&, U)> action,
				const function<void(U&, U)> composition,
				const function<void(U&)> twice,
				const function<U(U)> half,
				const T seg_id,
				const U act_id
			)
				: o(merge_function)
				, oo(action)
				, ooo(composition)
				, twice(twice)
				, half(half)
				, tid(seg_id)
				, uid(act_id)
			{
				ht = 1, sz = 1;
				while(sz < n) ht++, sz <<= 1;
				Sz = sz << 1;
				seg.assign(Sz, tid);
				act.resize(Sz, act_id);
				has_act.assign(Sz, false);
			}
		
		lazy_segment_tree(
				const vector<T>& data,
				const function<T(T, T)> merge_function,
				const function<void(T&, U)> action,
				const function<void(U&, U)> composition,
				const function<void(U&)> twice,
				const function<U(U)> half,
				const T seg_id,
				const U act_id
			)
				: lazy_segment_tree(
						data.size(),
						merge_function,
						action,
						composition,
						twice,
						half,
						seg_id,
						act_id
					)
			{
				copy(data.begin(), data.end(), seg.begin() + sz);
				for (int i = sz - 1; i >= 1; i--) seg[i] = o(seg[i << 1], seg[(i << 1) + 1]);
			}
		
		template<typename V, typename M, typename A>
		lazy_segment_tree(
				const V n_or_v,
				const M& merge_instance,
				const A& action_instance
			)
				: lazy_segment_tree(
					n_or_v,
					merge_instance.merge_function,
					action_instance.action,
					action_instance.composition,
					merge_instance.twice,
					merge_instance.half,
					merge_instance.id,
					action_instance.id
				)
			{
			}
		
		inline int lft (int i) {return i << 1;}
		inline int rgt (int i) {return (i << 1) + 1;}
		inline int upp (int i) {return i >> 1;}

		inline void propagate (
				int k,
				int L,
				int R
			)
			{
				if (has_act[k]) {
					oo(seg[k], act[k]);
					if (k < sz) {
						ooo(act[lft(k)], half(act[k]));
						ooo(act[rgt(k)], half(act[k]));
						has_act[lft(k)] = has_act[rgt(k)] = true;
					}
					act[k] = uid, has_act[k] = false;
				}
			}

		void update (
				int l,
				int r,
				T x,
				int k = 1,
				int L = 0,
				int R = -1
			)
			{
				if (R == -1) R = sz;
				if (k == 1) for (int i = 0; i < ht - 1; i++) twice(x);
				propagate(k, L, R);
				if (R <= l || r <= L) return;
				if (l <= L && R <= r) {
					ooo(act[k], x), has_act[k] = true;
					propagate(k, L, R);
				} else {
					int C = (L + R) >> 1;
					update(l, r, half(x), lft(k), L, C);
					update(l, r, half(x), rgt(k), C, R);
					seg[k] = o(seg[lft(k)], seg[rgt(k)]);
				}
			}
		
		T query (
				int l,
				int r,
				int k = 1,
				int L = 0,
				int R = -1
			)
			{
				if (R == -1) R = sz;
				propagate(k, L, R);
				if (R <= l || r <= L) return tid;
				if (l <= L && R <= r) {
					propagate(k, L, R);
					return seg[k];
				} else {
					int C = (L + R) >> 1;
					T lv = query(l, r, lft(k), L, C);
					T rv = query(l, r, rgt(k), C, R);
					seg[k] = o(seg[lft(k)], seg[rgt(k)]);
					return o(lv, rv);
				}
			}

		void print(int w = 4) {
			for (int i(1), last(2), output_size(w << ht); last <= Sz; last <<= 1, output_size >>= 1) {
				for (; i < last; i++) {
					cout << right << setw(w);
					cout << (seg[i] != tid ? to_string(seg[i]) : "");
					cout << setw(2) <<	"<";
					cout << left << setw(output_size - w - 2);
					cout << (has_act[i] ? to_string(act[i]) : "");
				}
				cout << endl;
			}
		}
};