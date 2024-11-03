extends MovingEntity


func _ready():
	var builder : SimpleEntityBuilder = SimpleEntityBuilder.new()
	builder.set_data(EntityDataImpl.new())
	
	set_entity(builder.get_entity());
	
	var input : HeroInput = HeroInput.new()
	
	input.add_trigger("CameraState1")
	input.add_trigger("CameraState2")
	input.add_trigger("CameraState3")
	
	set_input_component(input)