extends MovingEntity

func _ready():
	var builder : SimpleEntityBuilder = SimpleEntityBuilder.new()
	var interactor : ArcInteractor = ArcInteractor.new();
	interactor.set_element_id("40edb4e9-7904-40ea-9281-ac8657d32578")
	builder.set_interaction(interactor)
	builder.set_data(EntityDataImpl.new())
	
	
	set_entity(builder.get_entity());
