//
// Created by Yeo Shu Heng on 6/2/25.
//

#ifndef ORDER_H
#define ORDER_H

#include "json.hpp"

#include <string>

typedef nlohmann::json json;

class Order {
  private:
    const std::string asset;
    const std::string side;
    const std::string type;
    const float quantity;

  public:
    Order(const std::string &asset_, const std::string &side_, const std::string &type_, const float quantity_) {
      asset = asset_;
      side = side_;
      type = type_;
      quantity = quantity_;
    };

    std::string getAsset() const { return asset; };

    std::string getSide() const { return side; };

    std::string getType() const { return type; };

    float getQuantity() const { return quantity; };

    json toJson() {
      json orderJson;
      orderJson["symbol"] = asset;
      orderJson["side"] = side;
      orderJson["type"] = type;
      orderJson["quantity"] = quantity;
      return orderJson;
    };
}

class LimitOrder : public Order {
  private:
    const std::string timeToForce;

  public:
    LimitOrder(const std::string &asset_,
               const std::string &side_,
               const std::string &type_,
               const float quantity_,
               const std::string timeToForce_) : Order(asset_, side_, type_, quantity_)
    { timeToForce = timeToForce_; }

    float getTimeToForce() const { return timeToForce; };

    json toJson() override final {
      json orderJson = Order::toJson();
      orderJson["timeInForce"] = timeToForce;
      return orderJson;
    }
}

class StopLimitOrder : public LimitOrder {
  private:
    const float stopPrice;
  public:
  StopLimitOrder(const std::string &asset_,
             const std::string &side_,
             const std::string &type_,
             const float quantity_,
             const std::string timeToForce_,
             const float stopPrice_) : LimitOrder(asset_, side_, type_, quantity_)
    { stopPrice = stopPrice_; }

  float getStopPrice() const { return stopPrice; };

  json toJson() override final {
    json orderJson = LimitOrder::toJson();
      orderJson["stopPrice"] = stopPrice;
    return orderJson;
  }
}

#endif //ORDER_H
