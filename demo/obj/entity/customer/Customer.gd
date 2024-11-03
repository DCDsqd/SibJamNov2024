extends MovingEntity

func _ready():
	var builder : SimpleEntityBuilder = SimpleEntityBuilder.new()
	var interactor : CustomerInteractor = CustomerInteractor.new();
	#interactor.set_element_id("889f6461-b74e-4500-94cd-fe4587a59037")
	
	builder.set_interaction(interactor)
	var custommer_builder : CustommerBuilder = CustommerBuilder.new()
	
	custommer_builder.set_data(EntityDataImpl.new())
	custommer_builder.set_dialogue_id("889f6461-b74e-4500-94cd-fe4587a59037")
	custommer_builder.set_display_level(12)
	custommer_builder.set_min_req_level(20)
	custommer_builder.set_name("Francis")
	custommer_builder.set_fact_level(12)
	
	builder.set_data(custommer_builder.get_data())
	
	
	set_entity(builder.get_entity());
