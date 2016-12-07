function displayLists(jsonFile) {
    let content = $('#content');
    let html = "";
    content.html('<br />');
    $.each(jsonFile.person, (index, element) => {
        // content.append('<div class="person">');
        html += '<div class="person">';
        $.each(element, (index, value) => {
            html += `<p>${index}${value}</p>`;
            // content.append(`<p>${index}${value}</p>`);
        });
        // content.append('</div>');
        html += '</div>';
        content.append(html);
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
