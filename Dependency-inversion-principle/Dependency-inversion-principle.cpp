#include <iostream>
#include <memory>
#include <string>

// Абстракція логера
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& message) = 0;
};

// Конкретна реалізація: логер у файл
class FileLogger : public ILogger {
public:
    void log(const std::string& message) override {
        // У реальному випадку тут був би запис у файл
        std::cout << "[FileLogger]: " << message << std::endl;
    }
};

// Конкретна реалізація: логер у консоль
class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << "[ConsoleLogger]: " << message << std::endl;
    }
};

// Високорівневий модуль, який залежить від інтерфейсу ILogger
class Application {
public:
    explicit Application(std::unique_ptr<ILogger> logger)
        : logger_(std::move(logger)) {}

    void run() {
        logger_->log("Application is starting...");
        // Інша логіка застосунку
        logger_->log("Application is running...");
        logger_->log("Application is stopping...");
    }

private:
    std::unique_ptr<ILogger> logger_;
};

int main() {
    // Якщо ми хочемо змінити спосіб логування, достатньо передати інший логер
    std::unique_ptr<ILogger> logger = std::make_unique<FileLogger>();
    // Або: std::make_unique<ConsoleLogger>();

    Application app(std::move(logger));
    app.run();

    return 0;
}
