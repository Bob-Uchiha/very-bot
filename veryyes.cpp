#include <dpp/dpp.h>
#include <iostream>
#define PROJECT_NAME "veryyes"
//const std::string TOKEN = "put token here"
int main(int argc, char **argv) {
    int tickles;
    dpp::cluster bot(TOKEN,dpp::i_default_intents | dpp::i_message_content);
    bot.on_log(dpp::utility::cout_logger());
    dpp::commandhandler command_handler(&bot);
    command_handler.add_prefix("/");
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
            if(event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });
    bot.on_message_create([&bot](const dpp::message_create_t &event) {
            if(event.msg.content == "!embed") {
            dpp::embed embed = dpp::embed().
            set_color(dpp::colors::sti_blue).
            set_url("https://dpp.dev/").
            set_author("Nutes","https://dpp.dev/","https://dpp.dev/DPP-Logo.png").
            set_description("Nutes is cool").
            set_thumbnail("https://dpp.dev/DPP-Logo.png").
            add_field(
                    "MINECRAFT",
                    "YES",
                    true
            ).
            add_field(
                    "TEAM FOR 2",
                    "SPY",
                    true
            ).
            add_field(
                    "KONO DIO DA",
                    "ORA ORA ORA",
                    true
            ).
            set_image("https://dpp.dev/DPP-Logo.png").
            set_footer(dpp::embed_footer().set_text("footer text").set_icon("https://dpp.dev/DPP-Logo.png")).
            set_timestamp(time(0));

        bot.message_create(dpp::message(event.msg.channel_id, embed).set_reference(event.msg.id));
            }

            });

    bot.on_ready([&command_handler,&tickles](const dpp::ready_t &event) {
            command_handler.add_command("ping", {
                    {"param",dpp::param_info(dpp::pt_string, true, "optional param")}
                    },
                    [&command_handler](const std::string& command, const dpp::parameter_list_t& parameters, dpp::command_source src) {
                    std::string got_param;
                    if(!parameters.empty()) {
                    got_param = std::get<std::string>(parameters[0].second);
                    }
                    command_handler.reply(dpp::message("Pong! ->" + got_param),src);
                },
                "test ping"
            );
            command_handler.add_command(
                    "tickling",
                    {},
                    [&command_handler,&tickles](const std::string& command,const dpp::parameter_list_t& parameters, dpp::command_source src) {
                    command_handler.reply(dpp::message("People have been tickled " + tickles),src);
                            },
                            "tickle count"
                    );
            command_handler.register_commands();
        });
    bot.on_user_context_menu([&](const dpp::user_context_menu_t &event) {
            if(event.command.get_command_name() == "Tickle") {
            dpp::user user = event.get_user();
            dpp::user author = event.command.get_issuing_user();
            event.reply(author.get_mention() + " tickled " + user.get_mention());
            if(++tickles > 30) {
            std::cout << "TICKLE MONSTER";
            }
            }
            });

    bot.start(dpp::st_wait);
    return 0;
}
