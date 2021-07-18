#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#define ld long double
#define ll long long
using namespace std;
const ll maxn=1e4+5;

#define fori(e) for(ll i = 0; i < e; i++)
#define forj(e) for(ll j = 0; j < e; j++)
#define fork(e) for(ll k = 0; k < e; k++)





template< typename T, size_t N, size_t M >
void print2dArray( T(&theArray)[N][M]  ,ll n=N, ll m=M) {
    for ( ll x = 0; x < n; x ++ ) {
        for ( ll y = 0; y < m; y++ ) {
            cout << theArray[x][y] << " ";
        }
        cout<<"\n";
    }
}


template< typename T, size_t N >
void print_ar( T(&theArray)[N]  ,ll n=N) {
    for ( ll x = 0; x < n; x ++ )
    {
        cout << theArray[x] << " ";
    }
    cout<<"\n";
}



ll visited_values[maxn];
class process{
public:
    ll queue,Timeleft,Time_of_completion,ARRIVAL_TIME,TIME_QUANTA,BURSTTIME,WAIT_TIME,TIME_FOR_TURN;
    bool comp=false;
};

ll n;
vector<process>v;
queue<ll>QUEUE_1;
queue<ll>QUEUE_2;
void New_Process(ll curr_time) {
    fori(n)
        if (!visited_values[i] && v[i].ARRIVAL_TIME <= curr_time) {
            visited_values[i]=1;
            if (v[i].queue == 1) QUEUE_1.push(i);
            else QUEUE_2.push(i);
        }

}



int main() {
    cin >> n;
    ll time = 0;
    fori (n) {
        process p;
        cin >> p.queue >> p.ARRIVAL_TIME >> p.BURSTTIME >> p.TIME_QUANTA;
        p.Timeleft = p.BURSTTIME;
        p.Time_of_completion = -1;
        v.push_back(p);
    }
    New_Process(0);
    ll comp = 0;
    while (comp < n) {
        if (!QUEUE_1.empty()) {
            ll proc = QUEUE_1.front();
            QUEUE_1.pop();
            if (v[proc].Timeleft <= v[proc].TIME_QUANTA) {
                time += v[proc].Timeleft;
                v[proc].Time_of_completion = time;
                v[proc].Timeleft = 0;
                v[proc].comp = true;
                comp++;
                New_Process(time);
            } else {
                time += v[proc].TIME_QUANTA;
                v[proc].Timeleft -= v[proc].TIME_QUANTA;
                New_Process(time);
                QUEUE_1.push(proc);
            }
        } else if (!QUEUE_2.empty()) {
            ll proc = QUEUE_2.front();
            QUEUE_2.pop();
            if (v[proc].Timeleft <= v[proc].TIME_QUANTA) {
                time += v[proc].Timeleft;
                v[proc].Timeleft = 0;
                v[proc].comp = true;
                v[proc].Time_of_completion = time;
                comp++;
                New_Process(time);
            } else {
                time += v[proc].TIME_QUANTA;
                v[proc].Timeleft -= v[proc].TIME_QUANTA;
                New_Process(time);
                QUEUE_2.push(proc);
            }
        } else {
            time++;
        }
    }
    fori(n) {
        v[i].TIME_FOR_TURN = v[i].Time_of_completion - v[i].ARRIVAL_TIME;
        v[i].WAIT_TIME = v[i].TIME_FOR_TURN - v[i].BURSTTIME;
    }
    ld average_waiting_time = 0;
    ld turn_around_time = 0;
    for (ll i = 0; i < n; i++) {
        average_waiting_time += v[i].WAIT_TIME;
        turn_around_time += v[i].TIME_FOR_TURN;
    }
    fori(n)
    {
        cout<<"PROCESS "<<i+1<<"\n";
        cout<<"ARRIVAL TIME:"<<v[i].ARRIVAL_TIME<<"\n";
        cout<<"BURST TIME:"<<v[i].BURSTTIME<<"\n";
        cout<<"TIME OF COMPLETION:"<<v[i].Time_of_completion<<"\n";
        cout<<"WAIT TIME: "<<v[i].WAIT_TIME<<"\n";
        cout<<"TURN TIME: "<<v[i].TIME_FOR_TURN<<"\n";
        cout<<"\n\n\n";
    }
    cout << "AVERAGE WAITING TIME : " << (average_waiting_time / n) << endl;
    cout << "AVERAGE TURNAROUND TIME: " << (turn_around_time / n);

    return 0;

}