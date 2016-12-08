function displayLists(jsonString) {
    // console.log(jsonFile['person']['-id']);
    let json = JSON.parse(jsonString);
    let content = $('#content');
    let html = "";
    content.html('<br />');
    $.each(json.person, (index, element) => {
        html += '<div class="person">';
        $.each(element, (index, value) => {
            html += `<p>${index}${value}</p>`;
        });
        html += '</div>';
        content.append(html);
        content.append('<br />');
    });

}

// $(document).on('click', '.dropdown-menu li a', function() {
//     let listName = $(this).text().trim().substring(0,1);
//     console.log('lol');
//     $.get('/', { "which": listName }, function (data) {
//         console.log(data);
//         $('#content').append(data);
//         console.log('lol');
//     });
// });

$(document).on('click', '.dropdown', function(e) {
    let listName = e.target.value;
    $.get('/', { which: listName }, function (data) {
        displayLists(data);
    });
});


$(function () {
    // loadListNames();
    'use strict';
});
