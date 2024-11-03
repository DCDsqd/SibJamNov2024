extends Button

@export var viewModel : CustomerViewModel

func _ready():
	connect("button_up", press)

func press():
	if(!viewModel):
		print("Button: viewModel is null")
		return
	
	viewModel.request_quest()
