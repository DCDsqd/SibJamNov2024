extends ModelEntity

func _ready():
	var builder : SimpleEntityBuilder = SimpleEntityBuilder.new()
	builder.set_interaction(PcInteractor.new())
	builder.set_data(EntityDataImpl.new())
	
	
	set_entity(builder.get_entity());
