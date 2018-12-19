#include <gmock/gmock.h>

#include <iostream>
#include <string>
#include "PlaceDescriptionService.h"
#include "Http.h"

using namespace std;
using namespace testing;

class APlaceDescriptionService : public Test
{
public:
    static const string ValidLatitude;
    static const string ValidLongitude;
};

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");

class HttpStub:: public Http
{
    void initialize() override {}
    string get(const string& url) const override
    {
        return R"({ "address":{ "road":"Drury Ln", "city":"Fountain", "state":"CO", "country":"US"} })";
    }
};

TEST_F(APlaceDescriptionService, ReturnDescriptionForValidLocation)
{
    HttpStub httpStub;
    PlaceDescriptionService service(&httpStub);

    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

    ASSERT_THAT(description, Eq("Durry Ln, Fountain, CO, US"));
}