#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

enum PulseStrength {
    LowPulse,
    HighPulse
};

class IModule {
   public:
    virtual void receiveSignal(PulseStrength signal, string moduleName) = 0;
};

queue<tuple<string, PulseStrength, string>> signalQueue;

int lowPulseCounter = 0;
int highPulseCounter = 0;

void sendSingal(PulseStrength signal, string moduleName, string sourceName) {
    if (signal == LowPulse) {
        lowPulseCounter++;
    } else {
        highPulseCounter++;
    }
    signalQueue.push(tuple<string, PulseStrength, string>(moduleName, signal, sourceName));
}

class FlipSwitch : public IModule {
   public:
    bool on;
    vector<string> connections;
    string name;
    void receiveSignal(PulseStrength signal, string moduleName) {
        if (signal == LowPulse) {
            PulseStrength output;
            if (on) {
                on = false;
                output = LowPulse;
            } else {
                on = true;
                output = HighPulse;
            }
            for (string str : connections) {
                sendSingal(output, str, name);
            }
        }
    };
    FlipSwitch(string moduleName, vector<string> moduleNames) {
        on = false;
        connections = moduleNames;
        name = moduleName;
    };
};

class Conjunction : public IModule {
   public:
    unordered_map<string, PulseStrength> memory;
    vector<string> connections;
    string name;
    void receiveSignal(PulseStrength signal, string moduleName) {
        memory[moduleName] = signal;
        set<PulseStrength> pulses;
        for (auto p : memory) {
            pulses.insert(p.second);
        }
        PulseStrength output;
        if (pulses.size() == 1 && pulses.find(HighPulse) != pulses.end()) {
            output = LowPulse;
        } else {
            output = HighPulse;
        }
        for (string str : connections) {
            sendSingal(output, str, name);
        }
    };

    Conjunction(string moduleName, vector<string> incomingConnections, vector<string> outGoingConnections) {
        for (string str : incomingConnections) {
            memory.insert(pair<string, PulseStrength>(str, LowPulse));
        }
        connections = outGoingConnections;
        name = moduleName;
    };
};

class Broadcaster : public IModule {
   public:
    vector<string> connections;
    string name;

    Broadcaster(vector<string> moduleNames) {
        connections = moduleNames;

        name = "broadcaster";
    };
    void receiveSignal(PulseStrength signal, string moduleName) {
        for (string str : connections) {
            sendSingal(signal, str, name);
        }
    };
};
unordered_map<string, IModule*> moduleMap;
void processQueue() {
    while (signalQueue.size() > 0) {
        tuple<string, PulseStrength, string> p = signalQueue.front();
        // string debug = (get<1>(p) == HighPulse) ? "high" : "low";
        // cout << get<2>(p) << " -" << debug << "-> " << get<0>(p) << endl;
        if (get<0>(p) != "rx") {
            moduleMap[get<0>(p)]->receiveSignal(get<1>(p), get<2>(p));
        }

        signalQueue.pop();
    }
}

void pushButton() {
    moduleMap["broadcaster"]->receiveSignal(LowPulse, "button");
    lowPulseCounter++;
    // cout << "button -low-> broadcaster" << endl;
    processQueue();
}

main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<string> conModuls;
    unordered_map<string, vector<string>> conIncomingMap;

    unordered_map<string, vector<string>> connectionMap;
    for (string line : lines) {
        vector<string> input = splitByChar(line, '-');
        string typeWithName = input[0].substr(0, input[0].size() - 1);
        vector<string> split = splitByChar(input[1].substr(1), ',');
        vector<string> connections;
        transform(split.begin(), split.end(), back_inserter(connections), [](const string& str) { return str.substr(1); });
        connectionMap.insert(pair<string, vector<string>>(typeWithName, connections));
        if (typeWithName[0] == '&') {
            conModuls.push_back(typeWithName);
        }
    }
    for (string conName : conModuls) {
        vector<string> incomings;
        for (pair<string, vector<string>> p : connectionMap) {
            int count = 0;
            for (string str : p.second) {
                if (str == conName.substr(1)) {
                    count++;
                }
            }
            if (count > 0) {
                incomings.push_back(p.first.substr(1));
            }
        }
        conIncomingMap.insert(pair<string, vector<string>>(conName, incomings));
    }

    for (pair<string, vector<string>> p : connectionMap) {
        if (p.first[0] == '%') {
            FlipSwitch* fs = new FlipSwitch(p.first.substr(1), p.second);
            moduleMap.insert(pair<string, IModule*>(p.first.substr(1), fs));
        } else {
            if (p.first[0] == '&') {
                Conjunction* con = new Conjunction(p.first.substr(1), conIncomingMap.find(p.first)->second, p.second);

                moduleMap.insert(pair<string, IModule*>(p.first.substr(1), con));
            } else {
                if (p.first == "broadcaster") {
                    Broadcaster* bro = new Broadcaster(p.second);
                    moduleMap.insert(pair<string, IModule*>(p.first, bro));
                }
            }
        }
    }
    for (size_t i = 0; i < 1000; i++) {
        pushButton();
    }

    cout << lowPulseCounter * highPulseCounter << endl;

    // vector<IModule*> mv;
    // FlipSwitch fs("name", {});
    // Conjunction con("name", {}, {});
    // mv.push_back(&fs);
    // mv.push_back(&con);
    // for (IModule* i : mv) {
    //     i->receiveSignal(LowPulse, "null");
    // }
}