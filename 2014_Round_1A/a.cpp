#include<algorithm>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

// algorithm (by contest analysis)
// Let a flip-sequence be a sequence of bits, that determines
// which switches to flip on the outlets.
// Let a good-flip-sequence be a bit-sequence that appilied on the
// switches allows all devices to be paired with one outlet and all
// outlets be paired with one device.

template<typename N>
N apply(N flip_sequence, N outlet) {
  return flip_sequence ^ outlet;
}

template<typename N, typename I>
vector<N> apply(N flip_sequence,
		I f_outlets, I l_outlets) {
  vector<N> outlets;
  while (f_outlets != l_outlets) outlets.push_back(apply(flip_sequence, *f_outlets++));
  return outlets;
}

template<typename N, typename I0, typename I1>
bool is_good_flip_sequence(N flip_sequence,
			   I0 f_outlets, I0 l_outlets,
			   I1 f_devices, I1 l_devices) {
// Precondition: size(f_outlets, l_outlets) == size(f_devices, l_devices)
// Precondition: devices are sorted.
  vector<N> outlets = apply(flip_sequence, f_outlets, l_outlets);
  sort(begin(outlets), end(outlets));
  auto mm = mismatch(f_devices, l_devices, begin(outlets));
  return mm.first == l_devices;
}

template<typename N>
int value(N fs) {
  int counter = 0;
  while (0 < fs) {
    if (fs & 1) ++counter;
    fs >>= 1;
  }
  return counter;
}

template<typename N>
inline N get_flip_sequence(N outlet, N device) {
  return outlet ^ device;
}

template<typename N, typename I>
vector<N> generate_flip_sequences(N outlet, I f_d, I l_d) {
  vector<N> result;
  while(f_d != l_d) {
    result.push_back(get_flip_sequence(outlet, *f_d));
    ++f_d;
  }
  return result;
}

template<typename N>
void solve(vector<N>& outlets, vector<N>& devices) {
  sort(begin(devices), end(devices));
  vector<N> fss = generate_flip_sequences(outlets[0], begin(devices), end(devices));
  N min_fs;
  int min = 1000;
  for (N fs : fss) {
    if (is_good_flip_sequence(fs, begin(outlets), end(outlets), begin(devices), end(devices))) {
      int val = value(fs);
      if (val < min) {
	min_fs = fs;
	min = val;
      }
    }
  }
    
  if (min == 1000) {
    cout << "NOT POSSIBLE" << endl;
  } else {
    cout << min << endl;
  }  
}

template<typename N>
N read_one(size_t l) {
  N result = 0;
  string s; cin >> s;
  for (char c: s) {
    result <<= 1;
    if (c == '1') ++result;
  }
  return result;
}

template <typename N>
vector<N> read(size_t n, size_t l) {
  vector<N> result;
  result.reserve(n);
  while (0 < n--) result.push_back(read_one<N>(l));
  return result;
}

int main() {
  typedef unsigned long long N;
  int T, n, l; cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> n >> l;
    vector<N> outlets = read<N>(n, l);
    vector<N> devices = read<N>(n, l);
    cout << "Case #" << t+1 << ": ";
    solve(outlets, devices);
  }
  return 0;
}

  

