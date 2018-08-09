from django.db import models
from multiselectfield import MultiSelectField

# Create your models here.
MY_CHOICES = (('item_key1', 'Item title 1.1'),
              ('item_key2', 'Item title 1.2'),
              ('item_key3', 'Item title 1.3'),
              ('item_key4', 'Item title 1.4'),
              ('item_key5', 'Item title 1.5'))

YEAR_IN_SCHOOL_CHOICES = (
        (FRESHMAN, 'Freshman'),
        (SOPHOMORE, 'Sophomore'),
        (JUNIOR, 'Junior'),
        (SENIOR, 'Senior'),
    )
class House(models.Model):
    #location = ?
    rent_fee = models.PositiveIntegerField()   ## 월세
    utility_fee = models.PositiveIntegerField()    ## 관리비
    building = models.Charfield()
