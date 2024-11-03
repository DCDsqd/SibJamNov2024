extends MovingEntity

func _ready():
	var builder : SimpleEntityBuilder = SimpleEntityBuilder.new()
	var interactor : ArcInteractor = ArcInteractor.new();
	interactor.set_element_id("889f6461-b74e-4500-94cd-fe4587a59037")
	builder.set_interaction(interactor)
	builder.set_data(EntityDataImpl.new())
	
	
	set_entity(builder.get_entity());
