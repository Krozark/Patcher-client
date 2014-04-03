#ifndef PATCHER_MAJ_HPP
#define PATCHER_MAJ_HPP

#include <string>
#include <iostream>

#include <Patcher/Config.hpp>

namespace patcher
{
    class Maj
    {
        public:
            Maj(const Maj&) = delete;
            Maj& operator=(const Maj&) = delete;

            Maj(Config& conf,int action,std::string filename,std::string url="");

            const int action; ///<choices=[(0,"unknow"),(1,"New"),(2,"Maj"),(3,"Deleted")]
            const std::string filename;///<the real file name
            const std::string url;///<the url to get the file (relative to Config::getUrl)

            bool idDone() const;///< if done (with success)

            bool apply(); ///< make the maj. return isDone()

            friend std::ostream& operator<<(std::ostream& output,const Maj& self);
        private:

            Config& config;

            bool done;///< is done?

            /**
             * \brief download to download/filename
             */
            bool download();

            /**
             * \brief rm filename
             */
            bool erase();

            /**
             * \brief download + erase + write
             */
            bool replace();

            /**
             * \brief mv filename.tmp filename
             */
            bool write();
    };
}
#endif
