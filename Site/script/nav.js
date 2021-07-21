var navHtml = "\
	<div class='navbar' id='navbar'>\
		<div class='items'>\
			<div class='logo'>\
				<a href='/'>\
					<ul>\
						<li>\
							Donkey Kong 64 Practice ROM\
						</li>\
					</ul>\
				</a>\
			</div>\
			<div class='links'>\
				<ul class='container text noselect'>\
					<li>\
						<a href='/' class='nav_link'>\
							<span>\
								<strong>\
									Home\
								</strong>\
							</span>\
						</a>\
					</li>\
					<li>\
						<a href='/versions?version=latest' class='nav_link'>\
							<span>\
								<strong>\
									Download\
								</strong>\
							</span>\
						</a>\
					</li>\
					<li>\
						<a href='/features' class='nav_link'>\
							<span>\
								<strong>\
									Manual\
								</strong>\
							</span>\
						</a>\
					</li>\
				</ul>\
			</div>\
		</div>\
	</div>";

document.getElementById("navigation").innerHTML = navHtml;
document.getElementById("tools_hover").addEventListener("click", toggleDropdown)

function homewarp() {
	window.location = "/home.html"
}

var toolbar_items = [
	{
		"text": "Object Locations",
		"link": "/map_data.html"
	},
	{
		"text": "Cutscene Data",
		"link": "/cutscene_data.html"
	},
	{
		"text": "Mad Jack Luck Calculator",
		"link": "/mj_luck_calculator.html"
	},
	{
		"text": "List RNG Values",
		"link": "/next_rng_values.html"
	},
	{
		"text": "Main Menu Event Calculator",
		"link": "/menu_events.html"
	},
	{
		"text": "Pufftoss Viewer",
		"link": "/pufftoss_viewer.html"
	},
	{
		"text": "Object Script Viewer",
		"link": "/object_script_viewer.html"
	},
	{
		"text": "DK64 Practice ROM",
		"link": "/practicerom.html"
	}
];

var spawnedDropdown = false;
function toggleDropdown() {
	if (spawnedDropdown) {
		console.log("Despawn")
		document.getElementById("navToolsContainer").remove()
		spawnedDropdown = false;
	} else {
		console.log("Spawn")
		var toolsContainer = document.createElement("div")
		toolsContainer.classList.add("toolsContainer")
		toolsContainer.classList.add("container")
		toolsContainer.setAttribute("id","navToolsContainer")
		var navhook = document.getElementById("navbar")
		console.log(navhook.getBoundingClientRect())
		var top_offset = navhook.getBoundingClientRect().bottom - 1
		toolsContainer.style.top = top_offset + "px";

		toolbar_items.forEach(item => {
			var toolItem = document.createElement("div")
			toolItem.classList.add("toolsContainer")
			toolItem.classList.add("item")
			var toolItem_href = document.createElement("a")
			toolItem_href.classList.add("toolsContainer")
			toolItem_href.classList.add("linkController")
			toolItem_href.setAttribute("href",item.link)
			var toolItem_text = document.createTextNode(item.text)

			toolItem_href.appendChild(toolItem_text)
			toolItem.appendChild(toolItem_href)
			toolsContainer.appendChild(toolItem)
		})
		// Tidy Up
		document.getElementsByTagName("body")[0].appendChild(toolsContainer)
		spawnedDropdown = true;
	}
}