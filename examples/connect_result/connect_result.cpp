#include <iostream>
using namespace std;

#include <chrono>
#include <cstdint>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <iostream>
#include <thread>

using namespace mavsdk;
using namespace std::this_thread;
using namespace std::chrono;

int main(int argc, char** argv)
{
    Mavsdk mavsdk;
    ConnectionResult connection_result;
    bool discovered_system = false;
    connection_result = mavsdk.add_any_connection(argv[1]);
    if (connection_result != ConnectionResult::Success){ return 1; }
    mavsdk.subscribe_on_new_system([&mavsdk, &discovered_system](){
        const auto system = mavsdk.systems().at(0);
        if(system -> is_connected()) { discovered_system = true; }

    });

std::this_thread::sleep_for(std::chrono::seconds(2));
if(!discovered_system) { return 1; }
const auto system = mavsdk.systems().at(0);
system -> register_component_discovered_callback(
    [](ComponentType comp_type) -> void {std::cout << unsigned(comp_type); }
);
return 0;
}