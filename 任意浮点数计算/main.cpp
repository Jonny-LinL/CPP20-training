/* Multi-precision floating-point numbers
 *
*/

#include <iostream>     // std::cout
#include <string>       // std::string

// add two number
const std::string add(const std::string a, const std::string b){
    size_t a_addBegin{};
    for(; *(a.rbegin() + a_addBegin) == '0'; a_addBegin++){};
    // std::cout << "a ends with " << a_addBegin << " '0'.\n";
    size_t b_addBegin{};
    for(; *(b.rbegin() + b_addBegin) == '0'; b_addBegin++){};
    // std::cout << "b ends with " << b_addBegin << " '0'.\n";

    size_t a_dotpos{a_addBegin};
    for(; *(a.rbegin() + a_dotpos) != '.'; a_dotpos++){};
    // std::cout << "a'dot at " << a_dotpos << " .\n";
    size_t b_dotpos{b_addBegin};
    for(; *(b.rbegin() + b_dotpos) != '.'; b_dotpos++){};
    // std::cout << "b'dot at " << b_dotpos << " .\n";

    size_t a_smallPartLen{a_dotpos - a_addBegin};
    size_t b_smallPartLen{b_dotpos - b_addBegin};
    size_t a_intPartLen{size(a) - (a_dotpos+1)};
    size_t b_intPartLen{size(b) - (b_dotpos+1)};
    std::string c( (a_intPartLen > b_intPartLen? a_intPartLen:b_intPartLen) +
                   (a_smallPartLen > b_smallPartLen? a_smallPartLen:b_smallPartLen) + 2, '0' );
    // std::cout << "length of c is " << size(c) << "\n";
    size_t i{};
    int tens{};
    int ones{};
    // add small part
    if(a_smallPartLen > b_smallPartLen){
        for(; i < a_smallPartLen - b_smallPartLen; ++i){
            *(c.rbegin() + i) = *(a.rbegin() + a_addBegin + i);
        }
        for(; i < a_smallPartLen; ++i){
            
            int a_onedigit{*(a.rbegin() + a_addBegin + i) - '0'};
            int b_onedigit{*(b.rbegin() + b_addBegin + i - (a_smallPartLen - b_smallPartLen)) - '0'};
            int add_ab = a_onedigit + b_onedigit + tens;
            ones = add_ab >= 10 ? add_ab-10 : add_ab;
            tens = add_ab >= 10 ? 1 : 0;
            *(c.rbegin() + i) = ones + '0';
        }
    }else{
        for(; i < b_smallPartLen - a_smallPartLen; ++i){
            *(c.rbegin() + i) = *(b.rbegin() + b_addBegin + i);
        }
        for(; i < b_smallPartLen; ++i){
            int b_onedigit{*(b.rbegin() + b_addBegin + i) - '0'};
            int a_onedigit{*(a.rbegin() + a_addBegin + i - (b_smallPartLen - a_smallPartLen)) - '0'};
            int add_ab = b_onedigit + a_onedigit + tens;
            ones = add_ab >= 10 ? add_ab-10 : add_ab;
            tens = add_ab >= 10 ? 1 : 0;
            *(c.rbegin() + i) = ones + '0';
        }
    }
    // insert dot
    *(c.rbegin() + i) = '.';
    // add int part
    size_t j{i+1};
    if(a_intPartLen > b_intPartLen){
        for(; j - (i+1) < b_intPartLen; ++j){
            size_t kk{j - (i+1)};
            int a_onedigit{*(a.rbegin() + a_dotpos + 1 + kk) - '0'};
            int b_onedigit{*(b.rbegin() + b_dotpos + 1 + kk) - '0'};
            int add_ab = a_onedigit + b_onedigit + tens; 
            ones = add_ab >= 10 ? add_ab-10 : add_ab;
            tens = add_ab >= 10 ? 1 : 0;
            *(c.rbegin() + j) = ones + '0';
        }
        for(; j - (i+1) < a_intPartLen; ++j){
            size_t kk{j - (i+1)};
            int a_onedigit{*(a.rbegin() + a_dotpos + 1 + kk) - '0'};
            int add_ab = a_onedigit + tens;
            ones = add_ab >= 10 ? add_ab-10 : add_ab;
            tens = add_ab >= 10 ? 1 : 0;
            *(c.rbegin() + j) = ones + '0';
        }
        *(c.rbegin() + j) = tens + '0';
    }else{
        for(; j - (i+1) < a_intPartLen; ++j){
            size_t kk{j - (i+1)}; 
            int b_onedigit= {*(b.rbegin() + b_dotpos + 1 + kk) - '0'};
            int a_onedigit= {*(a.rbegin() + a_dotpos + 1 + kk) - '0'};
            int add_ab = a_onedigit + b_onedigit + tens; 
            ones = add_ab >= 10 ? add_ab-10 : add_ab;
            tens = add_ab >= 10 ? 1 : 0;
            *(c.rbegin() + j) = ones + '0';
        }
        for(; j - (i+1) < b_intPartLen; ++j){
            size_t kk{j - (i+1)};
            int b_onedigit{*(b.rbegin() + b_dotpos + 1 + kk) - '0'};
            int add_ab = b_onedigit + tens;
            ones = add_ab >= 10 ? add_ab-10 : add_ab;
            tens = add_ab >= 10 ? 1 : 0;
            *(c.rbegin() + j) = ones + '0';
        }
        *(c.rbegin() + j) = tens + '0';
    }
    if(*(c.begin()) == '0') c.erase(0,1);

    return c;
}



// main examples
int main() {

    // example 1
    const std::string a{"2342.14767987989765000"};
    const std::string b{"353425435.67896983634600"};
    auto c = add(a, b);     // 353427777.82664971624365
    std::cout << "--------------------" << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << c << std::endl;
    std::cout << "--------------------" << std::endl;

    // example 2
    const std::string a2{"3.4567"};
    const std::string b2{"6."};
    auto c2 = add(a2, b2);     // 9.4567
    std::cout << "--------------------" << std::endl;
    std::cout << "a = " << a2 << std::endl;
    std::cout << "b = " << b2 << std::endl;
    std::cout << "a + b = " << c2 << std::endl;
    std::cout << "--------------------" << std::endl;

    // example 3
    const std::string a3{"9.9967000"};
    const std::string b3{"999.060"};
    auto c3 = add(a3, b3);     // 1009.0567
    std::cout << "--------------------" << std::endl;
    std::cout << "a = " << a3 << std::endl;
    std::cout << "b = " << b3 << std::endl;
    std::cout << "a + b = " << c3 << std::endl;
    std::cout << "--------------------" << std::endl;
    
    return 0;
}


