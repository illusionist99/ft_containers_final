 #include <iostream>
#include <map>
# include "Map/map.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 4 // the ft::Map methods can be slower up to std::map methods * TIME_FAC (MAX 20)


template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}


time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}
// int main() {

//     std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method "
//               << "] --------------------]\t\t\033[0m";
//     {
//         bool cond(false);
        

//         std::map<char, int> m;
//         ft::Map<char, int> ft_m;

//         cond = m.size() == ft_m.size() && m.empty() == ft_m.empty();

//         // first insert function version (single parameter):
//         m.insert(std::pair<char, int>('a', 100));
//         m.insert(std::pair<char, int>('z', 200));

//         ft_m.insert(ft::pair<char, int>('a', 100));
//         ft_m.insert(ft::pair<char, int>('z', 200));

//         cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

//         std::pair<std::map<char, int>::iterator, bool> ret;
//         ft::pair<ft::Map<char, int>::iterator, bool> ft_ret;

//         ret = m.insert(std::pair<char, int>('z', 500));
//         ft_ret = ft_m.insert(ft::pair<char, int>('z', 500));

//         cond = cond && ret.second == ft_ret.second;

//         // second insert function version (with hint position):
//         std::map<char, int>::iterator it = m.begin();
//         ft::Map<char, int>::iterator ft_it = ft_m.begin();
//         m.insert(it, std::pair<char, int>('b', 300));
//         m.insert(it, std::pair<char, int>('c', 400));

//         ft_m.insert(ft_it, ft::pair<char, int>('b', 300));
//         ft_m.insert(ft_it, ft::pair<char, int>('c', 400));

//         cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

//         // third insert function version (range insertion):
//         std::map<char, int> anothermap;
//         ft::Map<char, int> ft_anothermap;
//         anothermap.insert(m.begin(), m.find('c'));
//         ft_anothermap.insert(ft_m.begin(), ft_m.find('c'));
//         cond = cond && (anothermap.size() == ft_anothermap.size() && anothermap.empty() == ft_anothermap.empty());

//         cond = cond && compareMaps(ft_m.begin(), ft_m.end(), m.begin(), m.end()) && compareMaps(ft_anothermap.begin(), ft_anothermap.end(), anothermap.begin(), anothermap.end());
//         EQUAL(cond);
//     }

//     std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method "
//               << "] --------------------]\t\t\033[0m";

//     {
//         bool cond(false);
       
//         std::map<char, int> m;
//         ft::Map<char, int> ft_m;
//         std::map<char, int>::iterator it;
//         ft::Map<char, int>::iterator ft_it;

//         // insert some values:
//         ft_m['a'] = 10;
//         ft_m['b'] = 20;
//         ft_m['c'] = 30;
//         ft_m['d'] = 40;
//         ft_m['e'] = 50;
//         ft_m['f'] = 60;

//         m['a'] = 10;
//         m['b'] = 20;
//         m['c'] = 30;
//         m['d'] = 40;
//         m['e'] = 50;
//         m['f'] = 60;

//         cond = m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         it = m.find('b');
//         ft_it = ft_m.find('b');

//         cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second);
//         m.erase(it);       // erasing by iterator
//         ft_m.erase(ft_it); // erasing by iterator

//         cond = cond && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         int ret = m.erase('c');       // erasing by key
//         int ft_ret = ft_m.erase('c'); // erasing by key

//         cond = cond && ret == ft_ret && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         it = m.find('e');
//         ft_it = ft_m.find('e');

//         cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second) && m.size() == ft_m.size();

//         m.erase(it, m.end());          // erasing by range
//         ft_m.erase(ft_it, ft_m.end()); // erasing by range

//         cond = cond && m.empty() == ft_m.empty() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         /* ---------- Testing some edge cases ---------- */

//         std::map<int, std::string> m2;
//         ft::Map<int, std::string> ft_m2;

//         for (size_t i = 0; i < 1e5; i++)
//         {
//             m2.insert(std::make_pair(i, "string1"));
//             ft_m2.insert(ft::make_pair(i, "string1"));
//         }

//         std::map<int, std::string>::reverse_iterator it2 = m2.rbegin();
//         ft::Map<int, std::string>::reverse_iterator ft_it2 = ft_m2.rbegin();

//         m2.erase(m2.begin());
//         ft_m2.erase(ft_m2.begin());

//         cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

//         m2.erase(it2->first);
//         ft_m2.erase(ft_it2->first);

//         cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

//         std::map<int, std::string> m3;
//         ft::Map<int, std::string> ft_m3;
//         std::vector<int> vec;
//         std::vector<int> ft_vec;
//         std::random_device randDev;
//         std::mt19937 generator(randDev());
//         std::uniform_int_distribution<int> distr(0, 1e8);

//         for (size_t i = 0; i < 1e6; i++)
//         {
//             m3.insert(std::make_pair(i, "string1"));
//             ft_m3.insert(ft::make_pair(i, "string1"));
//         }

//         for (size_t i = 0; i < 1e6; ++i)
//         {
//             int n = distr(generator);
//             int ret1 = m3.erase(n);
//             int ret2 = ft_m3.erase(n);

//             if (ret1 != ret2)
//             {
//                 cond = false;
//                 break;
//             }
//         }

//         if (!m3.empty())
//         {
//             m3.erase(m3.begin(), m3.end());
//             m3.erase(m3.begin(), m3.end());
//         }
//         if (!ft_m3.empty())
//         {
//             ft_m3.erase(ft_m3.begin(), ft_m3.end());
//             ft_m3.erase(ft_m3.begin(), ft_m3.end());
//         }
//         cond = cond && (m3.size() == ft_m3.size() && compareMaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()));

//         EQUAL(cond);
//     }

//     std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap method "
//               << "] --------------------]\t\t\033[0m";

//     {
        
//         bool cond = false;
//         std::map<char, int> foo, bar;
//         ft::Map<char, int> ft_foo, ft_bar;

//         foo['x'] = 100;
//         foo['y'] = 200;

//         ft_foo['x'] = 100;
//         ft_foo['y'] = 200;

//         cond = foo.size() == ft_foo.size() && bar.size() == ft_bar.size();

//         bar['a'] = 11;
//         bar['b'] = 22;
//         bar['c'] = 33;

//         ft_bar['a'] = 11;
//         ft_bar['b'] = 22;
//         ft_bar['c'] = 33;

//         cond = cond && foo.size() == ft_foo.size() && bar.size() == ft_bar.size() && compareMaps(foo.begin(), foo.end(), ft_foo.begin(), ft_foo.end()) && compareMaps(bar.begin(), bar.end(), ft_bar.begin(), ft_bar.end());

//         foo.swap(bar);
//         ft_foo.swap(ft_bar);

//         cond = cond && foo.size() == ft_foo.size() && bar.size() == ft_bar.size() && compareMaps(foo.begin(), foo.end(), ft_foo.begin(), ft_foo.end()) && compareMaps(bar.begin(), bar.end(), ft_bar.begin(), ft_bar.end());

//         std::map<std::string, std::string, std::greater<std::string> > m1, m2;
//         ft::Map<std::string, std::string, std::greater<std::string> > ft_m1, ft_m2;

//         m1["γ"] = "gamma";
//         m1["β"] = "beta";
//         m1["α"] = "alpha";
//         m1["γ"] = "gamma";

//         m2["ε"] = "eplsilon";
//         m2["δ"] = "delta";
//         m2["ε"] = "epsilon";

//         ft_m1["γ"] = "gamma";
//         ft_m1["β"] = "beta";
//         ft_m1["α"] = "alpha";
//         ft_m1["γ"] = "gamma";

//         ft_m2["ε"] = "eplsilon";
//         ft_m2["δ"] = "delta";
//         ft_m2["ε"] = "epsilon";

//         const std::pair<std::string, std::string> &ref = *(m1.begin());
//         const std::map<std::string, std::string, std::greater<std::string> >::iterator iter = std::next(m1.begin());
//         const ft::pair<std::string, std::string> &ft_ref = *(ft_m1.begin());
//         const ft::Map<std::string, std::string, std::greater<std::string> >::iterator ft_iter = std::next(ft_m1.begin());

//         // std::cout << "──────── before swap ────────\n"
//         //           << "m1: " << m1 << "m2: " << m2 << "ref: " << ref
//         //           << "\niter: " << *iter << '\n';

//         cond = cond && ref.first == ft_ref.first && ref.second == ft_ref.second && iter->second == ft_iter->second && iter->first == ft_iter->first && m1.size() == ft_m1.size() && m2.size() && ft_m2.size();

//         m1.swap(m2);
//         ft_m1.swap(ft_m2);

//         // _---------------_ << ──────── after swap ──────── >> _---------------_

//         cond = cond && ref.first == ft_ref.first && ref.second == ft_ref.second && iter->second == ft_iter->second && iter->first == ft_iter->first && m1.size() == ft_m1.size() && m2.size() && ft_m2.size();

//         EQUAL(cond);
//     }
//     std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " clear method "
//               << "] --------------------]\t\t\033[0m";

//     {
       
//         bool cond(false);
//         std::map<char, int> m;
//         ft::Map<char, int> ft_m;

//         m['x'] = 100;
//         m['y'] = 200;
//         m['z'] = 300;

//         ft_m['x'] = 100;
//         ft_m['y'] = 200;
//         ft_m['z'] = 300;

//         cond = m.size() == ft_m.size();

//         m.clear();
//         ft_m.clear();

//         cond = cond && m.empty() == ft_m.empty() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         m['a'] = 1101;
//         m['b'] = 2202;
//         ft_m['a'] = 1101;
//         ft_m['b'] = 2202;

//         cond = cond && m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         m = std::map<char, int>();
//         ft_m = ft::Map<char, int>();

//         m.clear();
//         ft_m.clear();

//         cond = cond && m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         EQUAL(cond);
//     }
// }




int main ()
{
        bool cond(false);
        // erasing all the elements in the map;
        std::map<char, int> m;
        ft::Map<char, int> ft_m;
        std::map<char, int>::iterator it;
        ft::Map<char, int>::iterator ft_it;

        // insert some values:
        ft_m['a'] = 10;
        ft_m['b'] = 20;
        ft_m['c'] = 30;
        ft_m['d'] = 40;
        ft_m['e'] = 50;
        ft_m['f'] = 60;

        m['a'] = 10;
        m['b'] = 20;
        m['c'] = 30;
        m['d'] = 40;
        m['e'] = 50;
        m['f'] = 60;

        cond = m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        std::cout << "========000============\n";
        std::cout << (m.size() == ft_m.size()) << std::endl;
        std::cout << (compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end())) << std::endl;
        std::cout << "========000============\n";

        it = m.find('b');
        ft_it = ft_m.find('b');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second);
        
        std::cout << "========111============\n";
        std::cout << (it->first == ft_it->first) << std::endl;
        std::cout << (it->second == ft_it->second) << std::endl;
        std::cout << "========111============\n";
        m.erase(it);       // erasing by iterator
        ft_m.erase(ft_it); // erasing by iterator

        cond = cond && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());
        std::cout << "========222============\n";
        std::cout << (compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end())) << std::endl;
        std::cout << "========222============\n";
        int ret = m.erase('c');       // erasing by key
        int ft_ret = ft_m.erase('c'); // erasing by key

        cond = cond && ret == ft_ret && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        std::cout << "========333============\n";
        std::cout << (compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end())) << std::endl;
        std::cout << (ret == ft_ret)  <<" " <<  ret << " " << ft_ret << std::endl;
        std::cout << "========333============\n";

        it = m.find('e');
        ft_it = ft_m.find('e');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second) && m.size() == ft_m.size();


        std::cout << "========444============\n";
        std::cout << (it->first == ft_it->first) << std::endl;
        std::cout << (it->second == ft_it->second) << std::endl;
        std::cout << (m.size() == ft_m.size()) << std::endl;
        std::cout << "========444============\n";

        m.erase(it, m.end());          // erasing by range
        ft_m.erase(ft_it, ft_m.end()); // erasing by range

        cond = cond && m.empty() == ft_m.empty() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());


        std::cout << "========444============\n";
        std::cout << (m.empty() == ft_m.empty()) << std::endl;
        std::cout << (compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end())) << std::endl;
        // std::cout << (m.size() == ft_m.size()) << std::endl;
        std::cout << "========444============\n";
        /* ---------- Testing some edge cases ---------- */

        std::map<int, std::string> m2;
        ft::Map<int, std::string> ft_m2;

        for (size_t i = 0; i < 1e5; i++)
        {
            m2.insert(std::make_pair(i, "string1"));
            ft_m2.insert(ft::make_pair(i, "string1"));
        }

        std::map<int, std::string>::reverse_iterator it2 = m2.rbegin();
        ft::Map<int, std::string>::reverse_iterator ft_it2 = ft_m2.rbegin();

        m2.erase(m2.begin());
        ft_m2.erase(ft_m2.begin());

        cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        std::cout << "====================\n";
        std::cout << (m2.size() == ft_m2.size()) << std::endl;
        std::cout << (compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end())) << std::endl;
        std::cout << "====================\n";
        m2.erase(it2->first);
        ft_m2.erase(ft_it2->first);
        std::cout << "====================\n";
        cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());
        std::cout << "====================\n";

        std::cout << (m2.size() == ft_m2.size()) << std::endl;
        std::cout << (compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end())) << std::endl;

        std::map<int, std::string> m3;
        ft::Map<int, std::string> ft_m3;
        std::vector<int> vec;
        std::vector<int> ft_vec;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<int> distr(0, 1e8);

        for (size_t i = 0; i < 1e6; i++)
        {
            m3.insert(std::make_pair(i, "string1"));
            ft_m3.insert(ft::make_pair(i, "string1"));
        }

        for (size_t i = 0; i < 1e6; ++i)
        {
            int n = distr(generator);
            int ret1 = m3.erase(n);
            int ret2 = ft_m3.erase(n);

            if (ret1 != ret2)
            {
                cond = false;
                break;
            }
        }

        if (!m3.empty())
        {
            m3.erase(m3.begin(), m3.end());
            m3.erase(m3.begin(), m3.end());
        }
        if (!ft_m3.empty())
        {
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
        }

        std::cout << "====================\n";
        std::cout << (m3.size() == ft_m3.size()) << std::endl;
        std::cout << (compareMaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end())) << std::endl;
        std::cout << "====================\n";
        // std::cout << () << std::endl;
        cond = cond && (m3.size() == ft_m3.size() && compareMaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()));
        
        EQUAL(cond);
}