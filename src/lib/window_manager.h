
class WindowManager {
    public:
        WindowManager();
        ~WindowManager();

        void init();
        void run();

    private:
        void handleEvents();
};