#define CROW_MAIN

#include <iostream>
#include <crow/json.h>
#include <cpr/cpr.h>
#include "crow.h"
#include <ctime>

const int PORT = 80;
const std::string AzuraAPI_NP = "http://46.101.23.145/api/nowplaying/1";

void printLogo();
crow::json::wvalue getPart(std::string part);

int main()
{


    //Prints SailorRadio logo, as well as some basic info
    printLogo();

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
        });


    /// api / stable / song / current

    //Displays the current song being played and its related data

    CROW_ROUTE(app, "/api/stable/songs/current").methods("GET"_method)([](const crow::request& req) {
        return getPart("now_playing");
        });

    /// api / stable / song / recent

    //Displays the recent songs played

    CROW_ROUTE(app, "/api/stable/songs/recent").methods("GET"_method)([](const crow::request& req) {
        return getPart("song_history");
    });

    /// api / stable / radio / listeners

    //Displays the currently active listeners

    CROW_ROUTE(app, "/api/stable/radio/listeners").methods("GET"_method)([](const crow::request& req) {
        return getPart("listeners");
    });

    /// api / stable / radio / DJ

    //Returns the active DJ

    CROW_ROUTE(app, "/api/stable/radio/DJ").methods("GET"_method)([](const crow::request& req) {
        return getPart("live");
    });

    /// api / stable / schedule / current

    //Displays the currently live DJ and all of their data.

    /// api / stable / schedule / upcoming

    //Displays the upcoming DJs for the day.





    CROW_ROUTE(app, "/home")([]() {
        auto page = crow::mustache::load("home.html");
        crow::mustache::context ctx;
        return page.render(ctx);
    });

    CROW_ROUTE(app, "/api/presenter").methods("GET"_method)([](const crow::request& req) {
        crow::json::wvalue jsonResponse;
        jsonResponse["presenter-name"] = "Joe Mamma";
        jsonResponse["presenter-id"] = "1234-56-7890";
        jsonResponse["presenter-profile-image"] = "https://images.com/reallyCoolImage.png";

        return jsonResponse;
    });

    CROW_ROUTE(app, "/api/songs/queue").methods("GET"_method)([](const crow::request& req) {
        return "no";
    });







    CROW_ROUTE(app, "/api/songs/recent").methods("GET"_method)([](const crow::request& req) {
        //TODO return list of song objects
        return "Coming soon";
    });


    std::cout << "Starting webserver on port " << PORT << std::endl;
    app.port(PORT).multithreaded().run();
}



void printLogo() {
    //Yup line by line. Dont worry about it.
    std::cout << "                               ^!!~^:.            \n";
    std::cout << "                               :!!7?JJ?!^         \n";
    std::cout << "                                     :~?Y?~       \n";
    std::cout << "                               !???!^.  :7Y?:     \n";
    std::cout << "                 ..:^^~!!!~:.   ..^~?J7.  ~JJ:    \n";
    std::cout << "              .!J55PPPGGGGGPP5YJ!:   ~J?:  !J?.   \n";
    std::cout << "              ?YY5PYYYYJJJJJ??7!!^    ^J?. .?J~   \n";
    std::cout << "                 ?5~            .:^:  .7?:  !?~   \n";
    std::cout << "             7J??Y5J????????JJYY5555^        .    \n";
    std::cout << "            ^55?^^7Y555555555YJ77J557             \n";
    std::cout << "           ~YY5!   .~JYYYYY7^.   ~5YJ.            \n";
    std::cout << "           ?YYYY?~^:.!YYYYJ~...^~JYYYJ^           \n";
    std::cout << "            7YYYYYYYYYYYYYYYYJYYYYYYYY!           \n";
    std::cout << "   .:    .. !YYJJJYYYYY?.7YYYYYY?JJJ!.            \n";
    std::cout << "   !?^  .7!  ... .!YYYYJ^:JYYYJ^  .               \n";
    std::cout << "   !7~  .77.      :YYYYYYYYYYY?                   \n";
    std::cout << "   :77.  ^7!:     .~!^7YYYYY??!                   \n";
    std::cout << "    ^7!:  .~77~::.    .!777!:                     \n";
    std::cout << "     :!7~.  .:~!!!.                               \n";
    std::cout << "       :!7!^:                                     \n";
    std::cout << "         .^!77!!~~.                               \n";
    std::cout << "            ..:^^:                                \n\n";
    std::cout << "> SailorRadioCLI. Developed by Aurorelyn#4695 2022.. \n\n";
    //Came to the wrong house for well written code baybeeeeeeeeeeeeeeeeeeeeeeeee.
}

crow::json::wvalue getPart(std::string part) {
    cpr::Response r = cpr::Get(cpr::Url{ AzuraAPI_NP });
    std::cout << "Status code: " << r.status_code << std::endl;
    crow::json::rvalue apiResponse = crow::json::load(r.text);
    crow::json::wvalue jsonResponse;
    jsonResponse = apiResponse[part];

    return jsonResponse;
}