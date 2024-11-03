extends MovingEntity


func _ready():
	var builder : SimpleEntityBuilder = SimpleEntityBuilder.new()
	#builder.set_data(HeroData)
	var data : ContainerEntityData = ContainerEntityData.new()
	data.set_order_container(OrderContainer.new())
	builder.set_data(data)
	set_entity(builder.get_entity());
	
	var input : HeroInput = HeroInput.new()
	
	input.add_trigger("CameraState1")
	input.add_trigger("CameraState2")
	input.add_trigger("CameraState3")
	
	set_input_component(input)
