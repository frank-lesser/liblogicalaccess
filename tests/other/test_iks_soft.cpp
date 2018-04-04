#include <logicalaccess/iks/IslogKeyServer.hpp>
#include <thread>
#include <logicalaccess/logs.hpp>
#include <logicalaccess/plugins/lla-tests/macros.hpp>
#include <logicalaccess/iks/IKSRPCClient.hpp>

using namespace logicalaccess;
using namespace iks;

static std::string key_name;

static void test_big()
{
    iks::IKSRPCClient rpc(iks::IslogKeyServer::get_global_config());
    std::cout << "Testing with big payload" << std::endl;

    for (int count = 0; count < 1; ++count)
    {

        auto bytes = ByteVector{};
        for (int i = 0; i < 16 * 200; ++i)
            bytes.push_back(i);

        auto iv = ByteVector{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        auto encrypted = rpc.aes_encrypt(bytes, key_name, iv);
        std::cout << "Encrypted (big) = " << encrypted << std::endl;
        auto decrypted = rpc.aes_decrypt(encrypted, key_name, iv);
        std::cout << "Decrypted (big) = " << decrypted << std::endl;
        assert(bytes == decrypted);
    }
}

int test_grpc()
{
    iks::IslogKeyServer::IKSConfig config("10.100.0.49", 6565,
                                          "/home/xaqq/Documents/iks/crypto/arnaud.pem",
                                          "/home/xaqq/Documents/iks/crypto/arnaud.key",
                                          "/home/xaqq/Documents/iks/crypto/MyRootCA.pem");

    iks::IKSRPCClient rpc(config);
    std::cout << "random bytes: " << rpc.gen_random(42) << std::endl;
}

int main(int ac, char **av)
{
    iks::IslogKeyServer::configureGlobalInstance(
        "iksf", 6565, "/home/xaqq/Documents/iks/crypto/arnaud.pem",
        "/home/xaqq/Documents/iks/crypto/arnaud.key",
        "/home/xaqq/Documents/iks/crypto/MyRootCA.pem");

    /*    iks::IslogKeyServer::configureGlobalInstance("10.100.0.49",
                                                     6565,
                                                     "",
                                                     "",
                                                     "");*/
    iks::IKSRPCClient rpc(iks::IslogKeyServer::get_global_config());

    if (ac == 2)
        key_name = std::string(av[1]);
    else
        key_name = "00000000-0000-0000-0000-000000000000";

    // rpc.get_random(17);
    auto bytes = ByteVector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    auto iv    = ByteVector{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    auto encrypted = rpc.aes_encrypt(bytes, key_name, iv);
    std::cout << "Encrypted = " << encrypted << std::endl;
    auto decrypted = rpc.aes_decrypt(encrypted, key_name, iv);
    std::cout << "Decrypted: " << decrypted << std::endl;
    assert(bytes == decrypted);
    /*
        for (auto i = 0 ; i < 1; i++)
            test_big();*/
}