function showSide() {
    var sideButton = document.getElementById("showside");
    var siteName = document.getElementById("sitename");
    var spanMenu = document.querySelectorAll('.side-menu ul li a span');
    if (siteName.style.display == "none") {
        siteName.style.display = "block";
        sideButton.innerHTML = "<i class=\"fas fa-angle-double-left fa-fw\"></i>";
        [].forEach.call(spanMenu, function(link) {
            link.style.display = "inline-block";
        });
    } else {
        siteName.style.display = "none";
        sideButton.innerHTML = "<i class=\"fas fa-angle-double-right fa-fw\"></i>";
        [].forEach.call(spanMenu, function(link) {
            link.style.display = "none";
        });
    }
}