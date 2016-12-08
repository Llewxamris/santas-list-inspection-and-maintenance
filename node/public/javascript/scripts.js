function displayLists(jsonString) {
    // console.log(jsonFile['person']['-id']);
    let json = JSON.parse(jsonString);
    let content = $('#content');
    let toInsert = "";
    let fName = '';
    let lname = '';
    content.html('<br />');
    $.each(json.person, (index, element) => {
        toInsert = '';
        fName = '';
        lName = '';
        toInsert += '<div value="test" class="person">';
        $.each(element, (index, value) => {
            if(index === '-id') {
                toInsert += `<h3 class='id'>${value}</h3>`;
            }
            if(index === 'firstName') {
                fName = value;
            }
            if(index === 'lastName') {
                lName = value;
            }
        });
        toInsert += fName + ' ' + lName;
        toInsert += '</div>';
        content.append(toInsert);
        content.append('<br />');
    });

}

function displaySpecific(jsonString) {
    console.log(jsonString);
    let fuck = '{ "person": [{"-id": "3","firstName": "John","lastName": "Doe","age": "53","city": "London","curList": "L","details": "","dateUpdated": "0404 - 1212 - 2016"}]}';
    let json     = JSON.parse(fuck);
    let content  = $('#specific');
    let toInsert = '';
    let id;
    let fName;
    let lName;
    let age;
    let city;
    let deta;
    let date;

    content.html('');

    $.each(json.person, (index, element) => {
        $.each(element, (index, value) => {
            switch (index) {
              case '-id':
                id = value;
                break;
              case 'lastName':
                lName = value;
                break;
              case 'firstName':
                fName = value;
                break;
              case 'age':
                age = value; 
                break;
              case 'city':
                city = value;
                break;
              case 'details':
                deta = value;
                break;
              case 'dateUpdated':
                date = value;
                break;
              default:
                console.log(`Key:Value ${index}:${value} not handled.`);
            }
        });
        toInsert += '<div>';
        toInsert += 'Name: '         + fName + ' ' + lName + '<br />';
        toInsert += 'Age: '          + age   + '<br />';
        toInsert += 'City: '         + city  + '<br />';
        toInsert += 'Details: '      + deta  + '<br />';
        toInsert += 'Date Updated: ' + date  + '<br />';
        toInsert += '</div>';
        content.append(toInsert);
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

$(document).on('click', '.dropdown', (e) => {
    let listName = e.target.value;

    $.get('/', { which: listName },  (data) => {
        displayLists(data);
    });
});

$(document).on('click', '.person .id',  (e) => {
    let personId = $(e.target).text();

    $.get('/', { "id": personId }, (data) => {
        displaySpecific(data);
    });
});
 
$(function () {
    // loadListNames();
    'use strict';
});
