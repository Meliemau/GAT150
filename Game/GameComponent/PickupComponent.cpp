#include "PickupComponent.h"
#include "Engine.h"

using namespace nc;

PickupComponent::~PickupComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void PickupComponent::Create()
{
	std::cout << "Create Coin Called" << std::endl;
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickupComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PickupComponent::OnCollisionExit, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "audio/coin.wav");
}

void PickupComponent::Update()
{

}

void PickupComponent::OnCollisionEnter(const nc::Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	std::cout << "Pickup On Colision Called" << std::endl;

	if (istring_compare(actor->tag, "Player")) {
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");
		owner->destroy = true;
	}
}

void PickupComponent::OnCollisionExit(const nc::Event& event)
{

}


bool PickupComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PickupComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	return true;
}

