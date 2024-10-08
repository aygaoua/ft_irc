#ifndef Channel_HPP
#define Channel_HPP

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sys/socket.h>
#include"client.hpp"
#include "global.hpp"
#include "reply.hpp"

class Client;
class Channel
{
    private:
        std::string             name;
        std::vector<Client *>   ClientssHouse;
        std::string             topic;
        std::string             topic_setter;
        std::string             topic_time;
        std::string             channelTime;
        int                     mode;
        size_t                  limit;
        std::string             key;
        bool                    i;
        bool                    k;
        bool                    l;
        bool                    t;
        
    public:
        Channel();
        Channel(std::string name, std::string key);
        Channel(const Channel& copy);
        ~Channel();
        bool                    addToChannel(Client *client, std::string key);
        void                    removeFromChannel(Client *client);
        void                    setChannelName(std::string name);
        std::string             getChannelName();
        Client*                 getTheOperator();
        std::string             getChannelKey();
        std::vector<Client *>   GetClientssHouse();
        void                    set_topic(std::string topic);
        std::string             get_topic();
		void	                set_topic_setter(std::string topicsetter);
        std::string             get_topic_setter();
        void                    set_time_ctime();
        void                    setTheChannelTimeCreated();
        std::string             getTheChannelTimeCreated();
        std::string             get_time_ctime();
        size_t                  getChannelLimitNum();
        void	                add_i();
		void	                add_t();
		void	                add_k(std::string key);
		void	                add_l(size_t limit);
        void	                rm_i();
		void	                rm_t();
		void	                rm_k(std::string old_key);
		void	                rm_l();
        bool	                get_i();
		bool	                get_t();
		bool	                get_k();
		bool	                get_l();
        void                    set_mode(int mode_number);
        void                    init_modes();
        std::string             get_channel_mode();
    };
#endif
