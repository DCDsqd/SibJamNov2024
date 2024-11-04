extends MovingEntity

func _ready():
	var builder : SimpleEntityBuilder = SimpleEntityBuilder.new()
	var interactor : CustomerInteractor = CustomerInteractor.new();
	#interactor.set_element_id("889f6461-b74e-4500-94cd-fe4587a59037")
	
	builder.set_interaction(interactor)
	
	var data : EntityData = EntityDataImpl.new()
	builder.set_data(data)
	set_entity(builder.get_entity());
	
	var custommer_builder : CustommerBuilder = CustommerBuilder.new()
	custommer_builder.set_data(data)
	#custommer_builder.set_dialogue_id("889f6461-b74e-4500-94cd-fe4587a59037")
	#custommer_builder.set_display_level(12)
	#custommer_builder.set_min_req_level(20)
	#custommer_builder.set_name("Francis")
	#custommer_builder.set_fact_level(12)
	#custommer_builder.set_state(0)
	custommer_builder.set_sprite("vlad3000")
	
	builder.free()
	
	#print(get_entity().get_data().has_string("CustommerSpriteId"))
	
	set_behaivor(CustomerBehaivor.new())
	print("sdfadgf: ")
	print(get_entity().get_data().has_string("CustommerSpriteId"))
