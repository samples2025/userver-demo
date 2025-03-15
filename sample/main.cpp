#include <userver/components/minimal_server_component_list.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/clients/dns/component.hpp>
#include <userver/utils/daemon_run.hpp>

#include "controllers/webhook.hpp"

int main(int argc, char* argv[])
{
    userver::components::ComponentList list = userver::components::MinimalServerComponentList()
                                                .Append<sample::ControllerWebHook>()
                                                .Append<userver::components::HttpClient>()
                                                .Append<userver::clients::dns::Component>();

    return userver::utils::DaemonMain(argc, argv, list);
}
