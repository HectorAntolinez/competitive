#include <iostream>
#include <vector>
#include <algorithm>

/*
#define TESTING_TIME
#include <ctime>
#include <iomanip>//*/


using namespace std;

void seek(size_t& deadline, int64_t warlocks_p, vector<size_t>& power, size_t& harry_p, int64_t& track)
{
  size_t begining{1};
  size_t l{0};

  for(l; l < deadline; ++l)
  {
    warlocks_p += power[l];

    if(warlocks_p <= harry_p)
      continue;

    if(not l) // equal 0, which means no warlocks killed
      break;

    if(begining) //equal 1, which means I have not taken the big stack of the begining
      track += ((1 << l) - (1 << begining--) + 1);
    // the beginning's big stack have already been calculated so it ain't needed to do it again

    size_t it_aux {0};
    int64_t warlocks_p_aux{warlocks_p};

    for(it_aux; it_aux < l; ++it_aux)
    {
      warlocks_p_aux -= power[it_aux];
      if(warlocks_p_aux > harry_p)
        continue;

      track += 1;
      if(it_aux) //greater than 0, because the 0th warlock is already calculated
        seek(it_aux, warlocks_p_aux, power, harry_p, track);
    }
  }

  if(begining)
    /*
    this one was speacially nicer than the rest,
         I had a functional method but, for some unknown reason
    the 10th test case was being rejected, that was because of a reallly big
    2^n calculation. what had to be done was to prepare a little special
    case to kill myself with so I could become to this little conclusion.
    */

    if(l > 15)
    {
      size_t aux {15};
      l -= aux;

      int64_t aux_aux{1 << l};
      aux_aux *= (1 << aux);

      track += --aux_aux;
    }
    else track += ((1 << l) - (1 << begining) + 1);
    // this one was the (^^^^)  bad boy
}

int main()
{
  size_t warlocks_n;
  size_t harry_power;
  cin >> warlocks_n >> harry_power;

  vector<size_t> warlocks(warlocks_n);
  for(auto& damage : warlocks)
    cin >> damage;

  sort(warlocks.begin(), warlocks.end());
  while(warlocks.back() > harry_power)
    warlocks.pop_back();

  #ifdef TESTING_TIME
  clock_t prove = clock();
  #endif

    int64_t track{0};
    seek(warlocks_n, 0, warlocks, harry_power, track);
    cout << track << endl;


  #ifdef TESTING_TIME
  prove = clock() - prove;
  cout << setprecision(10);
  cout << fixed;
  cout << static_cast<double>(prove)/CLOCKS_PER_SEC << endl;
  #endif

  return 0;
}