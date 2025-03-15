#pragma once

#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/clients/http/client.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/component_context.hpp>

namespace sample {

class ControllerWebHook final
    : public userver::server::handlers::HttpHandlerBase
{
public:
    using HttpHandlerBase::HttpHandlerBase;

    ControllerWebHook(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context
    )
        : HttpHandlerBase(config, context),
        m_http_client(context.FindComponent<userver::components::HttpClient>().GetHttpClient())
    {}

    std::string HandleRequestThrow(const userver::server::http::HttpRequest&, userver::server::request::RequestContext&) const override {
        std::shared_ptr<userver::clients::http::Response> response = m_http_client.CreateRequest().url("http://icanhazip.com").get().perform();
        return {};
    }

    static constexpr std::string_view kName = "controller-webhook";

private:
    userver::clients::http::Client& m_http_client;
};

}
