extends ModelEntity

func _ready():
	var builder : SimpleEntityBuilder = SimpleEntityBuilder.new()
	var data : ContainerEntityData = ContainerEntityData.new()
	var container : OrderContainer = OrderContainer.new()
	
	var order_builder : OrderBuilder = OrderBuilder.new()
	
	order_builder.create_order()
	order_builder.set_descr("la la la")
	order_builder.set_fact_level(10)
	order_builder.set_name("monsters")
	order_builder.set_image("res://res/2d/hud/memory_1.png")
	container.add_order(order_builder.get_entity())
	
	data.set_order_container(container)
	builder.set_data(data)
	builder.set_interaction(OrderInteractor.new())
	
	
	
	set_entity(builder.get_entity());

