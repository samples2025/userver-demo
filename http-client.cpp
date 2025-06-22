#include <userver/clients/http/client.hpp>
#include <userver/engine/async.hpp>
#include <userver/engine/get_all.hpp>
#include <userver/engine/run_standalone.hpp>
#include <userver/http/http_version.hpp>
#include <userver/logging/log.hpp>
#include <userver/logging/logger.hpp>

namespace {

struct WorkerContext {
    userver::clients::http::Client& http_client;
};

void Worker(WorkerContext& context) {
    LOG_INFO() << "Worker started";
    auto request = context.http_client.CreateRequest().get("https://ya.ru");
    try {
        auto response = request.perform();
    } catch (const std::exception& e) {
        LOG_ERROR() << "Exception: " << e;
    } catch (...) {
        LOG_ERROR() << "Non-std::exception exception";
    }
    // LOG_INFO() << response->body();
    LOG_INFO() << "Worker stopped";
}

void DoWork() {
    auto& tp = userver::engine::current_task::GetTaskProcessor();
    userver::clients::http::Client http_client{
        {"", 1}, tp,
        std::vector<userver::utils::NotNull<userver::clients::http::Plugin*>>{}
    };
    http_client.SetMultiplexingEnabled(false);
    WorkerContext worker_context{ http_client };
    std::vector<userver::engine::TaskWithResult<void>> tasks;
    tasks.resize(1);
    tasks[0] = userver::engine::AsyncNoSpan(tp, &Worker, std::ref(worker_context));
    userver::engine::GetAll(tasks);
}

}

int main() {
    const auto level = userver::logging::LevelFromString("info");
    const userver::logging::DefaultLoggerGuard guard(
        userver::logging::MakeStdoutLogger("default", userver::logging::Format::kTskv, level)
    );
    userver::engine::RunStandalone(1, [&]() { DoWork(); });
    LOG_INFO() << "Program finished";
}
