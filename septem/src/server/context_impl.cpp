#include "server/context_impl.hpp"
#include "server/connectionsm.hpp"
#include "account.hpp"
//#include "paradice/character.hpp"
#include "server/client.hpp"
//#include "hugin/user_interface.hpp"
#include <boost/asio/strand.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>


namespace fs = boost::filesystem;


// ==========================================================================
// GET_ACCOUNTS_PATH
// ==========================================================================
static fs::path get_accounts_path()
{
    auto cwd = fs::current_path();
    auto accounts_path = cwd / "accounts";
    
 //   if (!fs::exists(accounts_path))
 //   {
 //       fs::create_directory(accounts_path);
  //  }
    
    return accounts_path;
}

// ==========================================================================
// GET_CHARACTERS_PATH
// ==========================================================================
static fs::path get_characters_path()
{
    auto cwd = fs::current_path();
    auto characters_path = cwd / "characters";
    
   // if (!fs::exists(characters_path))
   // {
  //      fs::create_directory(characters_path);
   // }
    
    return characters_path;
}

// ==========================================================================
// GET_CHARACTER_ADDRESS
// ==========================================================================
/*
static std::string get_character_address(
    std::shared_ptr<paradice::character> const &ch)
{
    auto prefix = ch->get_prefix();
    auto name   = ch->get_name();
    auto title  = ch->get_suffix();
    
    std::string address;
    
    if (!prefix.empty())
    {
        address += prefix + " ";
    }
    
    address += name;
    
    if (!title.empty())
    {
        address += " " + title;
    }
    
    return address;
}
*/
    
// ==========================================================================
// CONTEXT_IMPL IMPLEMENTATION STRUCTURE
// ==========================================================================
struct context_impl::impl
{
    impl(
        boost::asio::io_service                       &io_service
      , std::shared_ptr<odin::net::server>             server
      , std::shared_ptr<boost::asio::io_service::work> work)
      : strand_(io_service)
      , server_(server)
      , work_(work)
    {
    }
    
    // ======================================================================
    // ADD_CLIENT
    // ======================================================================
    void add_client(std::shared_ptr<client> const &cli)
    {
        clients_.push_back(cli);
        
    }

    // ======================================================================
    // REMOVE_CLIENT
    // ======================================================================
    void remove_client(std::shared_ptr<client> const &cli)
    {
        clients_.erase(
            std::remove(
                clients_.begin()
              , clients_.end()
              , cli)
          , clients_.end());
    }
	

    // ======================================================================
    // UPDATE_NAMES
    // ======================================================================
    /*
    void update_names()
    {
        std::vector<std::string> names;
        
        for (auto &cur_client : clients_)
        {
            auto character = cur_client->get_character();
            
            if (character != NULL)
            {
                auto name = get_character_address(character);
                
                if (!name.empty())
                {
                    names.push_back(name);
                }
            }
        }
        
        for (auto &cur_client : clients_)
        {
            auto user_interface = cur_client->get_user_interface();
            
            if (user_interface != NULL)
            {
                user_interface->update_wholist(names);
            }
        }
    }
	*/

    // ======================================================================
    // LOAD_ACCOUNT
    // ======================================================================
	
    void load_account(
        std::string const &name, std::shared_ptr<account> &acct)
    {
        auto account_path = get_accounts_path() / name;
        
      //  if (fs::exists(account_path))
      //  {
      //      std::ifstream in(account_path.string().c_str());
      //      boost::archive::xml_iarchive ia(in);
            
       //     acct = std::make_shared<paradice::account>();
      //      ia >> boost::serialization::make_nvp("account", *acct);
       // }
    }
	

    // ======================================================================
    // SAVE_ACCOUNT
    // ======================================================================
    void save_account(std::shared_ptr<account> const &acct)
    {
       // auto account_path = get_accounts_path() / acct->username();
        
      //  std::ofstream out(account_path.string().c_str());
      //  boost::archive::xml_oarchive oa(out);
       // oa << boost::serialization::make_nvp("account", *acct);
    }
/*
    // ======================================================================
    // LOAD_CHARACTER
    // ======================================================================
    void load_character(
        std::string const                    &name,
        std::shared_ptr<paradice::character> &ch)
    {
        auto character_path = get_characters_path() / name;
        
        //if (fs::exists(character_path))
        //{
         //   std::ifstream in(character_path.string().c_str());
        //    boost::archive::xml_iarchive ia(in);
            
        //    ch = std::make_shared<paradice::character>();
        //    ia >> boost::serialization::make_nvp("character", *ch);
       // }
    }

    // ======================================================================
    // SAVE_CHARACTER
    // ======================================================================
    void save_character(std::shared_ptr<paradice::character> const &ch)
    {
        auto character_path = get_characters_path() / ch->get_name();
        
       // std::ofstream out(character_path.string().c_str());
       // boost::archive::xml_oarchive oa(out);
        //oa << boost::serialization::make_nvp("character", *ch);
    }
	*/

    boost::asio::strand                            strand_;
    std::shared_ptr<odin::net::server>             server_;
    std::shared_ptr<boost::asio::io_service::work> work_;
    std::vector<std::shared_ptr<client>> clients_;
   // server::connectionsm                           csm_;
};

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
context_impl::context_impl(
    boost::asio::io_service                        &io_service
  , std::shared_ptr<odin::net::server>              server
  , std::shared_ptr<boost::asio::io_service::work>  work)
    : pimpl_(new impl(io_service, server, work))
{
}
    
// ==========================================================================
// DESTRUCTOR
// ==========================================================================
context_impl::~context_impl()
{
}
    
// ==========================================================================
// GET_CLIENTS
// ==========================================================================
std::vector<std::shared_ptr<client>> context_impl::get_clients()
{
    return pimpl_->clients_;
}

// ==========================================================================
// ADD_CLIENT
// ==========================================================================
void context_impl::add_client(std::shared_ptr<client> const &cli)
{
    pimpl_->strand_.dispatch([this, cli]{pimpl_->add_client(cli);});
}

// ==========================================================================
// REMOVE_CLIENT
// ==========================================================================
void context_impl::remove_client(std::shared_ptr<client> const &cli)
{
    pimpl_->strand_.dispatch([this, cli]{pimpl_->remove_client(cli);});
}
/*
// ==========================================================================
// UPDATE_NAMES
// ==========================================================================
void context_impl::update_names()
{
    pimpl_->strand_.dispatch([this]{pimpl_->update_names();});
}
*/
// ==========================================================================
// GET_MONIKER
// ==========================================================================
/*
std::string context_impl::get_moniker(std::shared_ptr<septem::character> const &ch)
{
    std::string prefix = ch->get_prefix();
    std::string name   = ch->get_name();
    std::string title  = ch->get_suffix();
    
    std::string address;
    
    if (!prefix.empty())
    {
        address += prefix + " ";
    }
    
    address += name;
    
    if (!title.empty())
    {
        address += " " + title;
    }
    
    return address;
}
*/
 
// ==========================================================================
// LOAD_ACCOUNT
// ==========================================================================
std::shared_ptr<account> context_impl::load_account(std::string const &name)
{
    std::shared_ptr<account> acct;

    pimpl_->strand_.dispatch([this, &name, &acct]{
        pimpl_->load_account(name, acct);
    });

    return acct;
}

// ==========================================================================
// SAVE_ACCOUNT
// ==========================================================================
void context_impl::save_account(std::shared_ptr<account> const &acct)
{
    pimpl_->strand_.dispatch([this, acct]{pimpl_->save_account(acct);});
}
/*
// ==========================================================================
// LOAD_CHARACTER
// ==========================================================================
std::shared_ptr<paradice::character> context_impl::load_character(
    std::string const &name)
{
    std::shared_ptr<paradice::character> ch;
    pimpl_->strand_.dispatch([this, &name, &ch]{
        pimpl_->load_character(name, ch);
    });
    
    return ch;
}

// ==========================================================================
// SAVE_CHARACTER
// ==========================================================================
void context_impl::save_character(std::shared_ptr<paradice::character> const &ch)
{
    pimpl_->strand_.dispatch([this, ch]{pimpl_->save_character(ch);});
}
*/


// ==========================================================================
// SHUTDOWN
// ==========================================================================
void context_impl::shutdown()
{
    pimpl_->work_.reset();
    pimpl_->server_->shutdown();
}

// ==========================================================================
// GET_ACTIVE_ENCOUNTER
// ==========================================================================
/*
std::shared_ptr<paradice::active_encounter> context_impl::get_active_encounter()
{
    if (!gm_encounter) {
        gm_encounter = std::make_shared<paradice::active_encounter>();
    }

    return gm_encounter;
}

// ==========================================================================
// SET_ACTIVE_ENCOUNTER
// ==========================================================================
void context_impl::set_active_encounter(
    std::shared_ptr<paradice::active_encounter> const &enc)
{
    gm_encounter = enc;
}

// ==========================================================================
// IS_ACTIVE_ENCOUNTER_VISIBLE
// ==========================================================================
bool context_impl::is_active_encounter_visible() const
{
    return gm_encounter_visible;
}

// ==========================================================================
// SET_ACTIVE_ENCOUNTER_VISIBLE
// ==========================================================================
void context_impl::set_active_encounter_visible(bool visibility)
{
    gm_encounter_visible = visibility;

    for (auto &cli : pimpl_->clients_)
    {
        if (cli)
        {
            if (gm_encounter_visible)
            {
                cli->get_user_interface()->show_active_encounter_window();
            }
            else
            {
                cli->get_user_interface()->hide_active_encounter_window();
            }
        }
    }
}

// ==========================================================================
// UPDATE_ACTIVE_ENCOUNTER
// ==========================================================================
void context_impl::update_active_encounter()
{
    for (auto &cli : pimpl_->clients_)
    {
        if (cli)
        {
            cli->get_user_interface()->set_active_encounter(gm_encounter);
        }
    }
}
*/
