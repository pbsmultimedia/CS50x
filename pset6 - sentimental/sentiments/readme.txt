

Consumer Key (API Key)	OJnLEX3bYwNBU2ICQIf26GroY
Consumer Secret (API Secret)	qRvz2GRNLzTAXy6L8SWC1DefEr7zWPlFTFesqrdCh7P01tDTXF

export API_KEY=OJnLEX3bYwNBU2ICQIf26GroY

export API_SECRET=qRvz2GRNLzTAXy6L8SWC1DefEr7zWPlFTFesqrdCh7P01tDTXF

{% color=yellow if score > 0 color=green  elif score < 0 color=red endif %}



    {% if tweet.score > 0 %}

        {% set sentiment_class = "positive" %}

    {% elif tweet.score < 0 %}

        {% set sentiment_class = "negative" %}

    {% endif %}

    <span class="tweet {{ sentiment_class }}">

        {{ tweet.text }}

    </span>

    <small>

        score: {{ tweet.score }}

    </small>